#include "GameDisplay.hpp"
#include "Game.hpp"
#include "SuiteAndRank.hpp"
#include "tinyxml2.h"
using namespace tinyxml2;

GameDisplay::GameDisplay(){
    m_activeScreen=Screen::Menu;
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr<<"SDL_Init Error: "<<SDL_GetError() << std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr<<"IMG_Init Error: "<<IMG_GetError() << std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    if(TTF_Init() != 0)
    {
        std::cerr<<"TTF Error: "<<TTF_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("");
    }

    m_window = SDL_CreateWindow(
        "Card Game 66",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_windowWidth,
        m_windowHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if(!m_window){
        std::cerr<<"SDL Window Creation Error: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("SDL Window Creation Error");
    } 

    SDL_MaximizeWindow(m_window);

    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    m_windowWidth=w;
    m_windowHeight=h;
    m_cardWidth=m_windowWidth/9;
    m_cardHeight=m_windowHeight/3.4;


    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!m_renderer)
    {
        std::cerr<<"Renderer Creation Error: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("Renderer Creation Error");
    }

    m_font = TTF_OpenFont("resources/dejavu-fonts-ttf-2.37/ttf/DejaVuSans.ttf", 24);

    if(!m_font)
    {
        std::cerr<<"Font Opening Error: "<<TTF_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("Font Opening Error");
    }

    loadTextures("resources/Visual_Cards.xml");
    m_isCardSelected=false;
    m_selectedCard=CardId(MagyarRank::Placeholder,MagyarSuite::Placeholder);
    m_game = std::make_unique<Game>();
    m_EndRoundButton=Sprite(Vertex(m_windowWidth-300,  m_windowHeight - m_cardHeight - 70), TextureID::ButtonEndTheRound, 0, 140, 200);
    m_CloseTheCardButton=Sprite(Vertex(m_windowWidth-300, m_windowHeight - m_cardHeight +80), TextureID::ButtonCloseTheCard, 0, 140, 200);
    m_ContinueButton=Sprite(Vertex(m_windowWidth/2-150, m_windowHeight/2-100), TextureID::ButtonContinue, 0, 200, 300);

    m_menuButtons[0]=Sprite(Vertex(m_windowWidth/2-m_cardWidth, m_windowHeight/2-m_cardHeight/2-20-m_cardHeight/4), TextureID::ButtonMenuPlay, 0, m_cardHeight/2, m_cardWidth*2);
    m_menuButtons[1]=Sprite(Vertex(m_windowWidth/2-m_cardWidth, m_windowHeight/2-m_cardHeight/4), TextureID::ButtonMenuRules, 0, m_cardHeight/2, m_cardWidth*2);
    m_menuButtons[2]=Sprite(Vertex(m_windowWidth/2-m_cardWidth, m_windowHeight/2+20+m_cardHeight/4), TextureID::ButtonMenuExit, 0, m_cardHeight/2, m_cardWidth*2);
    m_menuButtons[3]=Sprite(Vertex(m_windowWidth/9, m_windowHeight-m_cardHeight/4-100), TextureID::ButtonMenuBack, 0, m_cardHeight/4, m_cardWidth/2);
}

GameDisplay::~GameDisplay()
{
        if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }

    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    TTF_Quit();      
    IMG_Quit();      
    SDL_Quit();      
}

void GameDisplay::loadTextures(const std::string& path) {
    XMLDocument doc;
    Deck m_deck;
    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);

    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);
     
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::string suiteStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();
        std::string cardArt = card->FirstChildElement("Path")->GetText();
        MagyarSuite suite;
        MagyarRank rank;

        if(suiteStr == "Rosu") suite = MagyarSuite::Rosu;
        else if(suiteStr == "Verde") suite = MagyarSuite::Verde;
        else if(suiteStr == "Ghinda") suite = MagyarSuite::Ghinda;
        else if(suiteStr == "Bata") suite = MagyarSuite::Bata;
        else throw std::runtime_error("Invalid suite: " + suiteStr);

        if(rankStr == "Doi"){
            rank = MagyarRank::Doi;
        } 
        else if(rankStr == "Trei"){
            rank = MagyarRank::Trei;
        } 
        else if(rankStr == "Cal"){
            rank = MagyarRank::Cal;
        } 
        else if(rankStr == "Craita"){
            rank = MagyarRank::Craita;
        } 
        else if(rankStr == "Tuz"){
            rank = MagyarRank::Tuz;
        } 
        else throw std::runtime_error("Invalid rank: " + rankStr);

        loadSingleTexture(CardIdToTextureId(CardId(rank, suite)), cardArt);
    }
    loadSingleTexture(TextureID::Back,"resources/cards/back.png");
    loadSingleTexture(TextureID::Placeholder,"resources/cards/placeholder.png");
    loadSingleTexture(TextureID::Background,"resources/Background.png");
    loadSingleTexture(TextureID::Button20End,"resources/Button20End.png");
    loadSingleTexture(TextureID::Button20Play,"resources/Button20Play.png");
    loadSingleTexture(TextureID::Button40End,"resources/Button40End.png");
    loadSingleTexture(TextureID::Button40Play,"resources/Button40Play.png");
    loadSingleTexture(TextureID::ButtonChangeTromf,"resources/ButtonChangeTromf.png");
    loadSingleTexture(TextureID::ButtonCloseTheCard,"resources/ButtonCloseTheCard.png");
    loadSingleTexture(TextureID::ButtonEndTheRound,"resources/ButtonEndTheRound.png");
    loadSingleTexture(TextureID::ButtonPlay,"resources/ButtonPlay.png");
    loadSingleTexture(TextureID::ButtonContinue,"resources/ButtonContinue.png");
    loadSingleTexture(TextureID::IconActions,"resources/icon1.png");
    loadSingleTexture(TextureID::IconTromf,"resources/icon3.png");
    loadSingleTexture(TextureID::ButtonMenuPlay,"resources/ButtonMenuPlay.png");
    loadSingleTexture(TextureID::ButtonMenuExit,"resources/ButtonMenuExit.png");
    loadSingleTexture(TextureID::ButtonMenuBack,"resources/ButtonMenuBack.png");
    loadSingleTexture(TextureID::ButtonMenuRules,"resources/ButtonMenuRules.png");
}

void GameDisplay::loadSingleTexture(TextureID id, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cerr << "Failed to load surface from " << path << ": " << IMG_GetError() << "\n";
            std::cin.get();
            throw std::runtime_error("Failed to load surface from "+path);
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
    
        if (!texture) {
            std::cerr << "Failed to create texture from " << path << ": " << SDL_GetError() << "\n";
        }
        try {
            m_textures.emplace(id, texture);
        } catch (const std::exception& e) {
            std::cerr << "Caught std::exception of type: " << typeid(e).name() << "\n";
            std::cerr << "What(): " << e.what() << "\n"; 
            std::cin.get();
        } catch (...) {
            std::cerr << "Caught unknown non-std exception!\n"; 
            std::cin.get();
        }
}

bool GameDisplay::renderBackground(){
    auto it = m_textures.find(TextureID::Background);
    if(it!= m_textures.end()){
        SDL_Texture* texture = it->second;
        SDL_Rect destination{0,0,m_windowWidth, m_windowHeight};
        SDL_RenderCopy(m_renderer, texture, nullptr, &destination);
        return true;
    }
    else{
        std::cerr << "Missing texture for card!\n";
        std::cin.get();
    }
    return false;
}

bool GameDisplay::renderCard(TextureID id, int x, int y, double rotate, float scale){
    auto it = m_textures.find(id);
    if(it!= m_textures.end()){
        SDL_Texture* texture = it->second;
        SDL_Rect destination{x,y,(int)(m_cardWidth*scale), (int)(m_cardHeight*scale)};
        SDL_RenderCopyEx(m_renderer, texture, nullptr, &destination, rotate, nullptr, SDL_FLIP_NONE);
        int temp_x = x+static_cast<int>(static_cast<float>(m_cardWidth)*scale)-m_cardWidth/8-10;
        if(textureIdToCardId(it->first).second==m_game->context().m_tromf.second)
        {
            renderTexture(TextureID::IconTromf,m_cardWidth/8, m_cardWidth/8, temp_x , y+10, rotate, scale);
            temp_x -=m_cardWidth/8+10;
        }    
        auto it = m_game->context().m_options.find(textureIdToCardId(id));
        if(it!= m_game->context().m_options.end() && it->second.size()>1){
            renderTexture(TextureID::IconActions,m_cardWidth/8, m_cardWidth/8, temp_x , y+10, rotate, scale);
        }
        return true;
    }
    else{
        std::cerr << "Missing texture for card!\n";   
        std::cin.get();
    }
    return false;
}

bool GameDisplay::renderTexture(TextureID id, int h, int w, int x, int y, double rotate, float scale){
    auto it = m_textures.find(id);
    if(it!= m_textures.end()){
        SDL_Texture* texture = it->second;
        SDL_Rect destination{x,y,(int)(w*scale), (int)(h*scale)};
        SDL_RenderCopyEx(m_renderer, texture, nullptr, &destination, rotate, nullptr, SDL_FLIP_NONE);
        return true;
    }
    else{
        std::cerr << "Missing texture! "<<textureIdToString(id)<<"\n";   
        std::cin.get();
    }
    return false;
}

bool GameDisplay::renderText(const std::string& text,int x, int y){

    int textWidth, textHeight;
    TTF_SizeText(m_font, text.c_str(), &textWidth, &textHeight);

    SDL_Rect textRect{x-textWidth/2, y-textHeight/2, textWidth, textHeight};

    SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, text.c_str(), {255, 255, 255, 255});
    if(!textSurface){
        std::cerr<<"Error creating text Surface: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("text surface create error");
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if(!texture){
        std::cerr<<"Error creating text texture: "<<SDL_GetError()<<std::endl;
        std::cin.get();
        throw std::runtime_error("text texture create error");
    }
    SDL_RenderCopy(m_renderer, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
    return true;
}


bool GameDisplay::renderOptions(TextureID id,int x, int y){
    auto it = m_game->context().m_options.find(textureIdToCardId(id));
    
    if(!m_game->context().m_options.empty() && it!=m_game->context().m_options.end() && it->second.size()>1){
        TextureID temp_ti;
        int w = (m_cardWidth/it->second.size());
        int padding=m_cardWidth-(it->second.size()*(w-3));
        int temp_x=x+padding;
        
        for(size_t i=0; i<it->second.size();i++)
        {
            switch(it->second.at(i)){
                case OptionType::Play:
                    temp_ti=TextureID::ButtonPlay;
                    break;
                case OptionType::Play20:
                    temp_ti=TextureID::Button20Play;
                    break;
                case OptionType::Play40:
                    temp_ti=TextureID::Button40Play;
                    break;
                case OptionType::Play20End:
                    temp_ti=TextureID::Button20End;
                    break;
                case OptionType::Play40End:
                    temp_ti=TextureID::Button40End;
                    break;
                case OptionType::ChangeTromf:
                    temp_ti=TextureID::ButtonChangeTromf;
                    break;
                default:
                    return false;
            }
            renderTexture(temp_ti, m_cardHeight/9, w, temp_x , y-(m_cardHeight/9)-5, 0, 1.0f);
            temp_x+=w+padding;
        }
    }
    return true;
}


bool GameDisplay::renderInteractiveElements(){
    for(const auto& button : m_buttonPositions)
    {
        if(textureIdToString(button.id)!="UnknownTextureID"&&textureIdToString(button.id)!="Background")
            renderTexture(button.id, button.h, button.w, button.pos.first , button.pos.second, button.wavePhase , button.scale);
    }
    return true;
}

void GameDisplay::renderRules()
{
    renderText("The Game Card 66 is a traditional Romanian game, played with Magyar cards, that only include the 2, 3, 4, 10 and 11 of each suit. ", m_windowWidth/2, 4*m_windowHeight/50);
renderText("It is played in only 2 players, players taking turns trying to beat each other's card. The first player plays a card, the second player plays another card. ", m_windowWidth/2, 5*m_windowHeight/50);
renderText("The player who won the hand will take both cards as points and will become the first player for the next hand of cards.", m_windowWidth/2, 6*m_windowHeight/50);
renderText("Each player has 5 cards in his hand and will draw after each hand is played, the player who won the previous hand will draw first.", m_windowWidth/2, 7*m_windowHeight/50);
renderText("The game is played in rounds, each round is finished when all cards have been played or one of the player finishes the game early.", m_windowWidth/2, 8*m_windowHeight/50);
renderText("Each round, the deck is shuffled and one card is put face-up under the deck. That card is called the Tromf.", m_windowWidth/2, 9*m_windowHeight/50);
renderText("It determins the suit that will dominate this round. Any card of the Tromf suite can take any other card.", m_windowWidth/2, 10*m_windowHeight/50);
renderText("The second player takes the hand if he can play a bigger card of the same suite as the first player, or play a Tromf.", m_windowWidth/2, 11*m_windowHeight/50);
renderText("If the first player played a Tromf card, the second player has to play a bigger Tromf card to beat it. The First player can do some actions on his turn that the second player can not: ", m_windowWidth/2, 12*m_windowHeight/50);
renderText("- He can end the game early ", m_windowWidth/2, 13*m_windowHeight/50);
renderText("- He can play a 20 or a 40. A 20 is played when the player has a 3 and a 4 of the same suite in his hand and you declare a 20 and play one of the cards.", m_windowWidth/2, 14*m_windowHeight/50);
renderText("  The 20 points will be added directly if the player has any other points taken, if not they will be added as soon as the player takes other points from usual plays.", m_windowWidth/2, 15*m_windowHeight/50);
renderText("  The player also has the option to call 20 and end the round , the same rules apply. The 40 is the same as the 20 but with 3 and 4 of Tromf. ", m_windowWidth/2, 16*m_windowHeight/50);
renderText("- He can change a 2 of Tromf with the Tromf card under the deck as long as there are more than 2 card remaining in the deck (including the tromf)", m_windowWidth/2, 17*m_windowHeight/50);
renderText("- He can close the card if there are more than 2 cards in the deck. Rules for closed cards bellow. Phases of the game", m_windowWidth/2, 18*m_windowHeight/50);
renderText("- As long as there are cards in the deck, including the Tromf at the bottom, and as long as the card is not closed, ", m_windowWidth/2, 19*m_windowHeight/50);
renderText("  the second player can play any cards, not being required to match the suite of the first card played that hand.", m_windowWidth/2, 20*m_windowHeight/50);
renderText("- If there are no cards left in the deck, the second player is required to match the suite of the card played by the first player, in the following manner: ", m_windowWidth/2, 21*m_windowHeight/50);
renderText("-- If the second player has the same suite of card in his hand as the card played by the First player, he has to play one of those cards. ", m_windowWidth/2, 22*m_windowHeight/50);
renderText("-- If the second player does not have the same suite of card as the card played by the First player, ", m_windowWidth/2, 23*m_windowHeight/50);
renderText("   but has Tromf in his hand (assuming the first played card is not Tromf) then he is required to play a tromf.", m_windowWidth/2, 24*m_windowHeight/50);
renderText("-- If the second player does not meet any of these conditions, he can play whatever card he feels like playing", m_windowWidth/2, 25*m_windowHeight/50);
renderText("-- Even if the Second player can take the hand with one of his cards, he is not required to.", m_windowWidth/2, 26*m_windowHeight/50);
renderText("- If the card is closed, the same rules apply as when there are no cards in the deck, the players do not draw any new cards when the card is closed. ", m_windowWidth/2, 27*m_windowHeight/50);
renderText("  The most significant difference when the card is closed are the points", m_windowWidth/2, 28*m_windowHeight/50);
renderText("The game is played until one player scores 11 round points.", m_windowWidth/2, 29*m_windowHeight/50);
renderText("Point system:", m_windowWidth/2, 30*m_windowHeight/50);
renderText("- If the game ended without a closed card, the round points as follows:", m_windowWidth/2, 31*m_windowHeight/50);
renderText("-- The player who took the last hand wins the round, no matter how many points he has.", m_windowWidth/2, 32*m_windowHeight/50);
renderText("--- If the losing player has at least 33 points for that round, the winner takes 1 round point.", m_windowWidth/2, 33*m_windowHeight/50);
renderText("--- If the losing player has less than 33 points, the winner takes 2 round points.", m_windowWidth/2, 34*m_windowHeight/50);
renderText("--- If the losing player has no points, the winner takes 3 round points.", m_windowWidth/2, 35*m_windowHeight/50);
renderText("- If the player ended the round early and he has at least 66 points", m_windowWidth/2, 36*m_windowHeight/50);
renderText("--- If the losing player has at least 33 points for that round, the winner takes 1 round point. ", m_windowWidth/2, 37*m_windowHeight/50);
renderText("--- If the losing player has less than 33 points, the winner takes 2 round points.", m_windowWidth/2, 38*m_windowHeight/50);
renderText("--- If the losing player has no points, the winner takes 3 round point", m_windowWidth/2, 39*m_windowHeight/50);
renderText("- If the player who closed the card has at least 66 points and he wins the last card or stops the round early, he wins 3 round points", m_windowWidth/2, 40*m_windowHeight/50);
renderText("- If a player closed the card but he did not win the last hand or he wins or stops the round but has less than 66 cards, the other player wins 3 round points", m_windowWidth/2, 41*m_windowHeight/50);
renderText("- If a player stops a round and has less than 66 points, he loses the round. Pointing rules are the same as when the game ended with all cards played without card closing.", m_windowWidth/2, 42*m_windowHeight/50);
float scale = m_menuButtons[m_menuButtons.size() - 1].isHovered ? 1.1f : 1.0f;
    int x = m_menuButtons[m_menuButtons.size() - 1].pos.first
            - ((m_menuButtons[m_menuButtons.size() - 1].w * scale
            - m_menuButtons[m_menuButtons.size() - 1].w) / 2);
    int y = m_menuButtons[m_menuButtons.size() - 1].pos.second
            - ((m_menuButtons[m_menuButtons.size() - 1].h * scale
            - m_menuButtons[m_menuButtons.size() - 1].h) / 2);
    renderTexture(
        m_menuButtons[m_menuButtons.size() - 1].id,
        m_menuButtons[m_menuButtons.size() - 1].h,
        m_menuButtons[m_menuButtons.size() - 1].w,
        x,
        y,
        0,
        scale
    );

}

void GameDisplay::render(){
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
    SDL_RenderClear(m_renderer);

    renderBackground();
    switch(m_activeScreen){
        case Screen::Menu:
        {
            for(size_t i=0;i<m_menuButtons.size()-1;++i){
                float scale = m_menuButtons[i].isHovered ? 1.1f : 1.0f;
                int x = m_menuButtons[i].pos.first
                        - ((m_menuButtons[i].w * scale
                        - m_menuButtons[i].w) / 2);
                int y = m_menuButtons[i].pos.second
                        - ((m_menuButtons[i].h * scale
                        - m_menuButtons[i].h) / 2);
                renderTexture(
                    m_menuButtons[i].id,
                    m_menuButtons[i].h,
                    m_menuButtons[i].w,
                    x,
                    y,
                    0,
                    scale
                );
            }
            break;
        }   
        case Screen::Main:
        {
            if(!m_game->context().m_isGameOverState)
            {
                m_game->getCurrentPlayerHand();
                int handSize = static_cast<int>(m_game->context().m_hand.size());
                int x = static_cast<int>((m_windowWidth - (handSize * m_cardWidth + (handSize - 1) * 20)) / 2);
                int y = m_windowHeight - m_cardHeight - m_windowHeight/10;
                m_handSize = handSize;

                for (int i = 0; i < handSize; i++) {
                    const auto& card = m_game->context().m_hand[i];

                    if (m_cardPositions[i].id == CardIdToTextureId(card->getCardId())) {
                        m_cardPositions[i].pos = Vertex(x, y);
                        m_cardPositions[i].wavePhase = i * 0.5f;
                    } else {
                        m_cardPositions[i] = Sprite(Vertex(x, y), CardIdToTextureId(card->getCardId()), i * 0.5f);
                    }

                    x += m_cardWidth + m_cardWidth/8;
                }

                for (size_t i = handSize; i < m_cardPositions.size(); i++) {
                    m_cardPositions[i] = Sprite(); 
                }


                Uint32 ticks = SDL_GetTicks(); 
                float waveSpeed = 0.005f;     
                float waveAmplitude = 10.0f;
                if(m_isCardSelected) 
                    waveAmplitude=0;

                for (size_t i = 0; i < m_handSize; i++) {
                    auto& lc = m_cardPositions[i];

                    lc.waveOffsetY = sin(ticks * waveSpeed + lc.wavePhase) * waveAmplitude;

                    lc.scale = (lc.isHovered && !m_isCardSelected)? 1.1f : 1.0f;
                    lc.scale = lc.isClicked ? 1.2f : lc.scale;

                    int renderX = lc.pos.first - ((m_cardWidth * lc.scale - m_cardWidth) / 2);
                    int renderY = lc.pos.second + static_cast<int>(lc.waveOffsetY)
                                - ((m_cardHeight * lc.scale - m_cardHeight) / 2);

                    renderCard(lc.id, renderX, renderY, 0.0, lc.scale);

                    if((lc.isHovered && !m_isCardSelected)){
                        renderOptions(lc.id, renderX, renderY);
                    }else if((m_isCardSelected && lc.isClicked)){
                        renderInteractiveElements();
                    }
                }

                x=m_windowWidth/2-m_cardWidth/2;
                y=(m_windowHeight-(3*m_cardHeight));
                
                if(m_game->context().m_isFirstPlayer)
                {
                    renderCard(TextureID::Placeholder,x,y, 0.0);
                    if(m_game->context().m_cardsLeft>2&&!m_game->context().m_isCardClosed)
                        renderTexture(m_CloseTheCardButton.id, m_CloseTheCardButton.h, m_CloseTheCardButton.w, m_CloseTheCardButton.pos.first,  m_CloseTheCardButton.pos.second, 0, 1.0f);
                    renderTexture(m_EndRoundButton.id, m_EndRoundButton.h, m_EndRoundButton.w, m_EndRoundButton.pos.first,  m_EndRoundButton.pos.second, 0, 1.0f);
                } 
                else{
                    renderCard(CardIdToTextureId(m_game->context().m_playedCard),x,y, 0.0);
                }

                if(m_game->context().m_cardsLeft>0){
                    x+=m_cardWidth+150;
                    y-=(m_cardHeight/2)-(m_cardWidth/2)-10;
                    renderCard(CardIdToTextureId(m_game->context().m_tromf),x, y, 90.0 );
                    x+=(m_cardWidth/2);
                    for(int i=0; i<static_cast<int>(m_game->context().m_cardsLeft/2); i++)
                    {
                        renderCard(TextureID::Back,x,y, 0.0);
                        x+=5;
                        y-=5;
                    }

                    if(m_game->context().m_cardsLeft>0){
                        x+=m_cardWidth/2;
                        y+=m_cardHeight/2;
                        renderText(std::to_string(m_game->context().m_cardsLeft),x,y);
                    }
                }
                renderText(m_game->context().m_playerName,100,100);
                renderText(std::to_string(m_game->context().m_points),100,130);
                if(m_game->context().m_isCardClosed)
                    renderText("Card is Closed!",m_windowWidth/2,m_windowHeight/8);
            }
            else{
                if(m_game->context().m_endRoundText.first.size()!=0) 
                {
                    renderText(m_game->context().m_endRoundText.first,m_ContinueButton.pos.first+m_ContinueButton.w/2,m_ContinueButton.pos.second-130);
                    renderText(m_game->context().m_endRoundText.second,m_ContinueButton.pos.first+m_ContinueButton.w/2,m_ContinueButton.pos.second-100);
                }    
                renderTexture(m_ContinueButton.id, m_ContinueButton.h, m_ContinueButton.w, m_ContinueButton.pos.first,  m_ContinueButton.pos.second, 0, 1.0f);
            }
            float scale = m_menuButtons[m_menuButtons.size() - 1].isHovered ? 1.1f : 1.0f;
            int x = m_menuButtons[m_menuButtons.size() - 1].pos.first
                    - ((m_menuButtons[m_menuButtons.size() - 1].w * scale
                    - m_menuButtons[m_menuButtons.size() - 1].w) / 2);
            int y = m_menuButtons[m_menuButtons.size() - 1].pos.second
                    - ((m_menuButtons[m_menuButtons.size() - 1].h * scale
                    - m_menuButtons[m_menuButtons.size() - 1].h) / 2);
            renderTexture(
                m_menuButtons[m_menuButtons.size() - 1].id,
                m_menuButtons[m_menuButtons.size() - 1].h,
                m_menuButtons[m_menuButtons.size() - 1].w,
                x,
                y,
                0,
                scale
            );
            break;
        }
        case Screen::Rules:
        {
            renderRules();
            break;
        }
        default:
        {
            break;
        }
    }
    
    SDL_RenderPresent(m_renderer);
    
}

int GameDisplay::handleEvents(){
    
    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                handleMouseHover(event.motion.x, event.motion.y);
                return 0;
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT){
                    return static_cast<int>(handleMouseClick(event.button.x, event.button.y));
                }
                break;
        }
    }

    return 0;
}

bool GameDisplay::pointOnTexture(int x, int y, int cardX, int cardY, int h, int w)
{
    return (x>cardX && x<cardX+w && y>cardY && y<cardY+h);
}

void GameDisplay::handleMouseHover(int x, int y){
    for (auto& card : m_cardPositions) {
        card.isHovered = false;
    }
    for (auto& card : m_cardPositions) {
        if (pointOnTexture(x, y, card.pos.first, card.pos.second, m_cardHeight, m_cardWidth)) {
            std::cout << "HOVERING" << std::endl;
            card.isHovered = true;
            break; 
        }
    }
    for (auto& button : m_buttonPositions) {
        button.isHovered=pointOnTexture(x, y, button.pos.first, button.pos.second, button.h, button.w);
    }

    for (auto& button : m_menuButtons) {
        button.isHovered =pointOnTexture(x, y, button.pos.first, button.pos.second, button.h, button.w);
    }
}

int GameDisplay::handleMouseClick(int x, int y){
    switch(m_activeScreen){
        case Screen::Menu:
        {
            if(pointOnTexture(x,y,m_menuButtons[0].pos.first,m_menuButtons[0].pos.second, m_menuButtons[0].h, m_menuButtons[0].w))
                m_activeScreen=Screen::Main;
            else if(pointOnTexture(x,y,m_menuButtons[1].pos.first,m_menuButtons[1].pos.second, m_menuButtons[1].h, m_menuButtons[1].w))
                m_activeScreen=Screen::Rules;
            else if(pointOnTexture(x,y,m_menuButtons[2].pos.first,m_menuButtons[2].pos.second, m_menuButtons[2].h, m_menuButtons[2].w))
                return-1;
            break;
        }
        case Screen::Main:
        {
            if(m_game->context().m_isGameOverState && pointOnTexture(x,y,m_ContinueButton.pos.first,m_ContinueButton.pos.second,m_ContinueButton.h,m_ContinueButton.w))
            {
                m_game->nextRound();
            }
            if(m_isCardSelected)
            {
                for(auto& button : m_buttonPositions)
                {
                    bool a = pointOnTexture(x,y,button.pos.first,button.pos.second, button.h, button.w);
                    if(a)
                    {
                        m_game->playOption(m_selectedCard, textureIdToOptionType(button.id));
                        m_isCardSelected=false;
                        m_selectedCard=CardId(MagyarRank::Placeholder,MagyarSuite::Placeholder);
                    }
                }
                for(auto& card : m_cardPositions)
                {
                    card.isClicked=false;
                    card.scale=1.0f;
                }    
                m_isCardSelected=false;
                m_buttonPositions.fill(Sprite());
            }else
            {
                int i=0;
                for(auto& card : m_cardPositions)
                {
                    if(pointOnTexture(x,y,card.pos.first, card.pos.second, m_cardHeight, m_cardWidth)){
                        auto it = m_game->context().m_options.find(textureIdToCardId(card.id));
                        if(it!= m_game->context().m_options.end())
                        {
                            if(card.isClicked==false){
                                card.isClicked=true;
                                m_selectedCard=textureIdToCardId(card.id);
                                m_isCardSelected=true;
                                m_selectedCardIndex=i;
                                for(size_t i=0;i<it->second.size();i++){
                                    int w = (m_cardWidth/it->second.size());
                                    int temp_x=(card.pos.first+i*(w+5)-5);
                                    m_buttonPositions[i]=Sprite(Vertex(temp_x, card.pos.second-80), optionTypeToTextureId(it->second[i]), 0, m_cardHeight/9, w);
                                }
                            }else if(card.isClicked==true)
                            {
                                m_isCardSelected=false;
                                m_selectedCard=CardId(MagyarRank::Placeholder,MagyarSuite::Placeholder);
                                card.isClicked=false;
                                m_buttonPositions.fill(Sprite());
                            }
                        }
                        else{
                            m_game->playOption(textureIdToCardId(card.id), OptionType::Play);
                        }
                        return 1;
                    }
                    ++i;
                }
                if(pointOnTexture(x,y,m_CloseTheCardButton.pos.first,m_CloseTheCardButton.pos.second, m_CloseTheCardButton.h, m_CloseTheCardButton.w))
                {
                    m_game->closeCard();
                }
                else if(pointOnTexture(x,y,m_EndRoundButton.pos.first,m_EndRoundButton.pos.second, m_EndRoundButton.h, m_EndRoundButton.w))
                {
                    m_game->endRound();
                }
            }
            if(pointOnTexture(x,y,m_menuButtons[3].pos.first,m_menuButtons[3].pos.second, m_menuButtons[3].h, m_menuButtons[3].w))
                m_activeScreen=Screen::Menu;
            break;
        }
        case Screen::Rules:
        {
            if(pointOnTexture(x,y,m_menuButtons[3].pos.first,m_menuButtons[3].pos.second, m_menuButtons[3].h, m_menuButtons[3].w))
                m_activeScreen=Screen::Menu;
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}

void GameDisplay::updatePositions()
{
    m_cardWidth=m_windowWidth/11;
    m_cardHeight=m_windowHeight/3.6f;
    int size=0;
    for(auto& button : m_buttonPositions)
    {
        if(textureIdToString(button.id)!="UnknownTextureID"&&textureIdToString(button.id)!="Background")
        {
            ++size;
        }
    }
    if(size>0){
        int i=0;
        for(auto& button : m_buttonPositions)
        {
            if(textureIdToString(button.id)!="UnknownTextureID"&&textureIdToString(button.id)!="Background")
            {
                button.h=m_cardHeight/9;
                button.w=m_cardWidth/size;
                button.pos.first=m_cardPositions[m_selectedCardIndex].pos.first+i*(button.w+5)-5;
                button.pos.second=m_cardPositions[m_selectedCardIndex].pos.second-2*button.h;
                ++i;
            }
        }
    }
        
    m_CloseTheCardButton.h=m_cardHeight/2-m_cardHeight/20;
    m_CloseTheCardButton.w=m_cardWidth* 1.1f;
    m_CloseTheCardButton.pos.first=m_windowWidth-(m_cardWidth*2);
    m_CloseTheCardButton.pos.second=m_windowHeight - m_cardHeight - m_windowHeight/10;
    
    m_EndRoundButton.h=m_cardHeight/2-m_cardHeight/20;
    m_EndRoundButton.w=m_cardWidth* 1.1f;
    m_EndRoundButton.pos.first= m_windowWidth-(m_cardWidth*2);
    m_EndRoundButton.pos.second=m_windowHeight - m_cardHeight - m_windowHeight/10+(m_cardHeight/2-m_cardHeight/20+20);
       
    m_ContinueButton.h=m_cardWidth*0.55f;
    m_ContinueButton.w=m_cardWidth;
    m_ContinueButton.pos.first=m_windowWidth/2-m_cardWidth/2;
    m_ContinueButton.pos.second=m_windowHeight/2-(m_cardWidth/2);

    m_menuButtons[0].h = m_cardHeight / 2;
    m_menuButtons[0].w = m_cardWidth * 2;
    m_menuButtons[0].pos.first  = m_windowWidth / 2 - m_cardWidth;
    m_menuButtons[0].pos.second = m_windowHeight / 2 - m_cardHeight / 2 - 20 - m_cardHeight / 4;
    m_menuButtons[0].id = TextureID::ButtonMenuPlay;
    m_menuButtons[0].wavePhase = 0.0f;

    m_menuButtons[1].h = m_cardHeight / 2;
    m_menuButtons[1].w = m_cardWidth * 2;
    m_menuButtons[1].pos.first  = m_windowWidth / 2 - m_cardWidth;
    m_menuButtons[1].pos.second = m_windowHeight / 2 - m_cardHeight / 4;
    m_menuButtons[1].id = TextureID::ButtonMenuRules;
    m_menuButtons[1].wavePhase = 0.0f;

    m_menuButtons[2].h = m_cardHeight / 2;
    m_menuButtons[2].w = m_cardWidth * 2;
    m_menuButtons[2].pos.first  = m_windowWidth / 2 - m_cardWidth;
    m_menuButtons[2].pos.second = m_windowHeight / 2 + 20 + m_cardHeight / 4;
    m_menuButtons[2].id = TextureID::ButtonMenuExit;
    m_menuButtons[2].wavePhase = 0.0f;

    m_menuButtons[3].h = m_cardHeight / 4;
    m_menuButtons[3].w = m_cardWidth / 2;
    m_menuButtons[3].pos.first  = m_windowWidth / 13;
    m_menuButtons[3].pos.second = m_windowHeight - m_cardHeight / 4 - 100;
    m_menuButtons[3].id = TextureID::ButtonMenuBack;
    m_menuButtons[3].wavePhase = 0.0f;

}

void GameDisplay::run(){
    bool isRunning = true;

    render();
    while(isRunning)
    {
        if(handleEvents()==-1)
            isRunning=false;
        render();
        SDL_Delay(16);
        
        m_game->update();
        int w, h;
        SDL_GetWindowSize(m_window, &w, &h);
        if(h!=m_windowWidth || w!=m_windowHeight){
            m_windowWidth=w;
            m_windowHeight=h;
            updatePositions();
        }
    }
}
#include "GameDisplay.hpp"
#include "Game.hpp"
#include "SuiteAndRank.hpp"
#include "tinyxml2.h"
using namespace tinyxml2;

GameDisplay::GameDisplay(){
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
    m_selectedCard=CardID(MagyarRank::Placeholder,MagyarSuite::Placeholder);
    m_game = std::make_unique<Game>();
    m_EndRoundButton=LocalizedTexture(Vertex(m_windowWidth-300,  m_windowHeight - m_cardHeight - 70), TextureID::ButtonEndTheRound, 0, 140, 200);
    m_CloseTheCardButton=LocalizedTexture(Vertex(m_windowWidth-300, m_windowHeight - m_cardHeight +80), TextureID::ButtonCloseTheCard, 0, 140, 200);
    m_ContinueButton=LocalizedTexture(Vertex(m_windowWidth/2-150, m_windowHeight/2-100), TextureID::ButtonContinue, 0, 200, 300);
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

    TTF_Quit();      // Always call, even if TTF_Init() fails later
    IMG_Quit();      // Same here
    SDL_Quit();      // Likewise
}

void GameDisplay::loadTextures(const std::string& path) {
    XMLDocument doc;
    Deck m_deck;
    if(doc.LoadFile(path.c_str()) != XML_SUCCESS)
        throw std::runtime_error("Failed to load XML from file "+path);

    //Getting the root of the Deck
    auto* root = doc.FirstChildElement("Deck");
    if(!root)
        throw std::runtime_error("Missing <Deck> Element "+path);
     
    //Getting all elements in Deck
    for(auto* card = root->FirstChildElement("Card"); card; card = card->NextSiblingElement("Card")){
        std::string suiteStr = card->FirstChildElement("Suite")->GetText();
        std::string rankStr = card->FirstChildElement("Rank")->GetText();
        std::string cardArt = card->FirstChildElement("Path")->GetText();
        MagyarSuite suite;
        MagyarRank rank;

        //get the suite
        if(suiteStr == "Rosu") suite = MagyarSuite::Rosu;
        else if(suiteStr == "Verde") suite = MagyarSuite::Verde;
        else if(suiteStr == "Ghinda") suite = MagyarSuite::Ghinda;
        else if(suiteStr == "Bata") suite = MagyarSuite::Bata;
        else throw std::runtime_error("Invalid suite: " + suiteStr);

        //get the rank
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

        loadSingleTexture(cardIdToTextureId(CardID(rank, suite)), cardArt);
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
        SDL_Rect destination{x,y,m_cardWidth*scale, m_cardHeight*scale};
        SDL_RenderCopyEx(m_renderer, texture, nullptr, &destination, rotate, nullptr, SDL_FLIP_NONE);
        int temp_x = x+static_cast<int>(static_cast<float>(m_cardWidth)*scale)-m_cardWidth/8-10;
        if(textureIdToCardId(it->first).second==m_game->m_context.m_tromf.second)
        {
            renderTexture(TextureID::IconTromf,m_cardWidth/8, m_cardWidth/8, temp_x , y+10, rotate, scale);
            temp_x -=m_cardWidth/8+10;
        }    
        auto it = m_game->m_context.m_options.find(textureIdToCardId(id));
        if(it!= m_game->m_context.m_options.end() && it->second.size()>1){
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
        SDL_Rect destination{x,y,w*scale, h*scale};
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
    //std::string cardsLeft=std::to_string(m_deck->cardsLeft());

    int textWidth, textHeight;
    TTF_SizeText(m_font, text.c_str(), &textWidth, &textHeight);

    SDL_Rect textRect{x-textWidth/2, y-textHeight/2, textWidth, textHeight};

    SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, text.c_str(), {255, 255, 255});
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
    auto it = m_game->m_context.m_options.find(textureIdToCardId(id));
    
    if(!m_game->m_context.m_options.empty() && it!=m_game->m_context.m_options.end() && it->second.size()>1){
        TextureID temp_ti;
        int w = (m_cardWidth/it->second.size());
        int padding=m_cardWidth-(it->second.size()*(w-3));
        int temp_x=x+padding;
        
        for(int i=0; i<it->second.size();i++)
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


bool GameDisplay::renderClickableOptions(){
    for(const auto& button : m_ButtonPositions)
    {
        if(textureIdToString(button.id)!="UnknownTextureID"&&textureIdToString(button.id)!="Background")
            renderTexture(button.id, button.h, button.w, button.pos.first , button.pos.second, button.wavePhase , button.scale);
    }
    return true;
}

void GameDisplay::render(){
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
    SDL_RenderClear(m_renderer);

    renderBackground();
    if(!m_game->m_context.m_isGameOverState)
    {//render the hand
        m_game->getCurrentPlayerHand();
        int handSize = static_cast<int>(m_game->m_context.m_hand.size());
        int x = static_cast<int>((m_windowWidth - (handSize * m_cardWidth + (handSize - 1) * 20)) / 2);
        int y = m_windowHeight - m_cardHeight - m_windowHeight/10;
        m_handSize = handSize;

        for (int i = 0; i < handSize; i++) {
            const auto& card = m_game->m_context.m_hand[i];

            // Preserve hover/scale state if the same card is already here
            if (m_cardPositions[i].id == cardIdToTextureId(card->getCardID())) {
                m_cardPositions[i].pos = Vertex(x, y);
                m_cardPositions[i].wavePhase = i * 0.5f;
            } else {
                // Overwrite with a new LocalizedTexture (resets hover)
                m_cardPositions[i] = LocalizedTexture(Vertex(x, y), cardIdToTextureId(card->getCardID()), i * 0.5f);
            }

            x += m_cardWidth + m_cardWidth/8;
        }

        // If fewer cards than before, clear the unused slots
        for (int i = handSize; i < m_cardPositions.size(); i++) {
            m_cardPositions[i] = LocalizedTexture(); // or some "empty" state
        }


        Uint32 ticks = SDL_GetTicks(); 
        float waveSpeed = 0.005f;     
        float waveAmplitude = 10.0f;
        if(m_isCardSelected) 
            waveAmplitude=0;

        for (int i = 0; i < m_handSize; i++) {
            auto& lc = m_cardPositions[i];

            // idle wave
            lc.waveOffsetY = sin(ticks * waveSpeed + lc.wavePhase) * waveAmplitude;

            // apply hover scaling
            lc.scale = (lc.isHovered && !m_isCardSelected)? 1.1f : 1.0f;
            lc.scale = lc.isClicked ? 1.2f : lc.scale;


            // compute adjusted position
            int renderX = lc.pos.first - ((m_cardWidth * lc.scale - m_cardWidth) / 2);
            int renderY = lc.pos.second + static_cast<int>(lc.waveOffsetY)
                        - ((m_cardHeight * lc.scale - m_cardHeight) / 2);

            renderCard(lc.id, renderX, renderY, 0.0, lc.scale);

            if((lc.isHovered && !m_isCardSelected)){
                renderOptions(lc.id, renderX, renderY);
            }else if((m_isCardSelected && lc.isClicked)){
                renderClickableOptions();
            }
        }

        x=m_windowWidth/2-m_cardWidth/2;
        y=(m_windowHeight-(3*m_cardHeight));
        
        if(m_game->m_context.m_isFirstPlayer)
        {
            //render placeholder
            renderCard(TextureID::Placeholder,x,y, 0.0);
            //render buttons
            if(m_game->m_context.m_cardsLeft>2&&!m_game->m_context.m_isCardClosed)
                renderTexture(m_CloseTheCardButton.id, m_CloseTheCardButton.h, m_CloseTheCardButton.w, m_CloseTheCardButton.pos.first,  m_CloseTheCardButton.pos.second, 0, 1.0f);
            renderTexture(m_EndRoundButton.id, m_EndRoundButton.h, m_EndRoundButton.w, m_EndRoundButton.pos.first,  m_EndRoundButton.pos.second, 0, 1.0f);
        } 
        else{
            //render played card
            renderCard(cardIdToTextureId(m_game->m_context.m_playedCard),x,y, 0.0);
        }

        if(m_game->m_context.m_cardsLeft>0){
            //render tromf
            x+=m_cardWidth+150;
            y-=(m_cardHeight/2)-(m_cardWidth/2)-10;
            renderCard(cardIdToTextureId(m_game->m_context.m_tromf),x, y, 90.0 );
            //render deck
            x+=(m_cardWidth/2);
            for(int i=0; i<static_cast<int>(m_game->m_context.m_cardsLeft/2); i++)
            {
                renderCard(TextureID::Back,x,y, 0.0);
                x+=5;
                y-=5;
            }

            //render deck size
            if(m_game->m_context.m_cardsLeft>0){
                x+=m_cardWidth/2;
                y+=m_cardHeight/2;
                renderText(std::to_string(m_game->m_context.m_cardsLeft),x,y);
            }
        }
        //render player name and score
        renderText(m_game->m_context.m_playerName,100,100);
        renderText(std::to_string(m_game->m_context.m_points),100,130);
        if(m_game->m_context.m_isCardClosed)
            renderText("Card is Closed!",m_windowWidth/2,m_windowHeight/8);
    }
    else{
        if(m_game->m_context.m_endRoundText.first.size()!=0) 
        {
            renderText(m_game->m_context.m_endRoundText.first,m_ContinueButton.pos.first+m_ContinueButton.w/2,m_ContinueButton.pos.second-130);
            renderText(m_game->m_context.m_endRoundText.second,m_ContinueButton.pos.first+m_ContinueButton.w/2,m_ContinueButton.pos.second-100);
        }    
        renderTexture(m_ContinueButton.id, m_ContinueButton.h, m_ContinueButton.w, m_ContinueButton.pos.first,  m_ContinueButton.pos.second, 0, 1.0f);
    }
    SDL_RenderPresent(m_renderer);
    
}

int GameDisplay::handleEvents(){
    
    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                std::cout<<"QUIT"<<std::endl;
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
        // reset all first
    for (auto& card : m_cardPositions) {
        card.isHovered = false;
    }

    // then set the hovered one
    for (auto& card : m_cardPositions) {
        if (pointOnTexture(x, y, card.pos.first, card.pos.second, m_cardHeight, m_cardWidth)) {
            std::cout << "HOVERING" << std::endl;
            card.isHovered = true;
            break; // stop at first hovered card
        }
    }
    for (auto& button : m_ButtonPositions) {
        if (pointOnTexture(x, y, button.pos.first, button.pos.second, button.h, button.w)) {
            std::cout << "HOVERING" << std::endl;
            button.isHovered = true;
            break; // stop at first hovered card
        }
    }
}

bool GameDisplay::handleMouseClick(int x, int y){
    std::cout<<"CLICK"<<std::endl;
    if(m_game->m_context.m_isGameOverState && pointOnTexture(x,y,m_ContinueButton.pos.first,m_ContinueButton.pos.second,m_ContinueButton.h,m_ContinueButton.w))
    {
        m_game->m_context.m_isGameOverState=false;
        m_game->nextRound();
    }
    if(m_isCardSelected)
    {
        std::cout<<"A card is selected "<<m_ButtonPositions.size()<<std::endl;
        for(auto& button : m_ButtonPositions)
        {
            bool a = pointOnTexture(x,y,button.pos.first,button.pos.second, button.h, button.w);
            std::cout<<a<<" x-"<<x<<" y-"<<y<<" posfirst-"<<button.pos.first<<" possecond-"<<button.pos.second<<" h"<<button.h<<" w"<<button.w<<std::endl;
            if(a)
            {
                std::cout<<"CLicked on option "<<std::endl;
                m_game->playOption(m_selectedCard, textureIdToOptionType(button.id));
                m_isCardSelected=false;
                m_selectedCard=CardID(MagyarRank::Placeholder,MagyarSuite::Placeholder);
            }
        }
        for(auto& card : m_cardPositions)
        {
            card.isClicked=false;
            card.scale=1.0f;
        }    
        m_ButtonPositions.fill(LocalizedTexture());
    }else{
        int i=0;
        for(auto& card : m_cardPositions)
        {
            if(pointOnTexture(x,y,card.pos.first, card.pos.second, m_cardHeight, m_cardWidth)){//card.second = CardID
                //handle option screen with m_game->m_context.m_options(card.second);
                auto it = m_game->m_context.m_options.find(textureIdToCardId(card.id));
                if(it!= m_game->m_context.m_options.end())
                {
                    if(card.isClicked==false){
                        card.isClicked=true;
                        m_isCardSelected=true;
                        m_selectedCardIndex=i;
                        for(int i=0;i<it->second.size();i++){
                            int w = (m_cardWidth/it->second.size());
                            int temp_x=(card.pos.first+i*(w+5)-5);
                            m_ButtonPositions[i]=LocalizedTexture(Vertex(temp_x, card.pos.second-80), optionTypeToTextureId(it->second[i]), 0, m_cardHeight/9, w);
                        }
                        for(const auto& button: m_ButtonPositions)
                            std::cout<<textureIdToString(button.id)<<std::endl;
                    }else if(card.isClicked==true)
                    {
                        m_isCardSelected=false;
                        m_selectedCard=CardID(MagyarRank::Placeholder,MagyarSuite::Placeholder);
                        card.isClicked=false;
                        m_ButtonPositions.fill(LocalizedTexture());
                    }
                }
                else{
                    std::cout<<"clicked on card "<<rankToString(textureIdToCardId(card.id).first)<<" "<<suiteToString(textureIdToCardId(card.id).second)<<std::endl;
                    m_game->playOption(textureIdToCardId(card.id), OptionType::Play);
                }
                return true;
            }
            ++i;
        }
    }
    m_isCardSelected=false;
    m_selectedCard=CardID(MagyarRank::Placeholder,MagyarSuite::Placeholder);
    
    
    if(pointOnTexture(x,y,m_CloseTheCardButton.pos.first,m_CloseTheCardButton.pos.second, m_CloseTheCardButton.h, m_CloseTheCardButton.w))
    {
        std::cout<<"Clicked on Close The Card "<<std::endl;
        m_game->closeCard();
    }
    else if(pointOnTexture(x,y,m_EndRoundButton.pos.first,m_EndRoundButton.pos.second, m_EndRoundButton.h, m_EndRoundButton.w))
    {
        std::cout<<"Clicked on End the Round "<<std::endl;
        m_game->endRound();
    }
    return false;
}

void GameDisplay::updatePositions()
{
    m_cardWidth=m_windowWidth/11;
    m_cardHeight=m_windowHeight/3.6f;
    int size=0;
    for(auto& button : m_ButtonPositions)
    {
        if(textureIdToString(button.id)!="UnknownTextureID"&&textureIdToString(button.id)!="Background")
        {
            ++size;
        }
    }
    if(size>0){
        int i=0;
        for(auto& button : m_ButtonPositions)
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
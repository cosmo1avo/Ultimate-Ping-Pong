class animation
{
public:
    animation(sf::Texture* texture, sf::Vector2u imagecount, float switchtime)
    {
        this->imagecount = imagecount;
        this->switchtime = switchtime;
        totaltime = 0.0f;
        currentimage.x=0;
        uvrect.width=texture->getSize().x / float(imagecount.x);
        uvrect.height=texture->getSize().y / float(imagecount.y);
    }
    void update(int row, float deltatime, bool faceright)
    {
        currentimage.y = row;
        totaltime += deltatime;
        if (totaltime >= switchtime)
        {
            totaltime -= switchtime;
            currentimage.x++;
            if (currentimage.x >= imagecount.x)
            {
                currentimage.x=0;
            }
        }
        uvrect.top=currentimage.y * uvrect.height;
        if(faceright)
        {
            uvrect.left=currentimage.x * uvrect.width;
            uvrect.width = abs(uvrect.width);
        }
        else
        {
            uvrect.left=(currentimage.x + 1) * abs(uvrect.width);
            uvrect.width = -abs(uvrect.width);
        }
    }
    sf::IntRect getuvrect()
    {
        return this->uvrect;
    }
private:
    sf::IntRect uvrect;
    sf::Vector2u imagecount;
    sf::Vector2u currentimage;

    float totaltime;
    float switchtime;
};
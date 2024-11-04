void resizeview(const sf::RenderWindow& window,sf::View& view)
{
    float aspectratio = float(window.getSize().x)/float(window.getSize().y);
    view.setSize(VIEW_HEIGHT*aspectratio,VIEW_HEIGHT);
}
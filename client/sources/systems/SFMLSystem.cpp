
/* Created by Romain FOUYER on 05/11/2019 at 10:57. */


#include "SFMLSystem.hpp"

#include <csignal>

#include "systems/SystemManager.hpp"
#include "utilities/GameWrapper.hpp"
#include "systems/NetworkSystem.hpp"

#include "worlds/WorldManager.hpp"
#include "worlds/MenuWorld.hpp"
#include "worlds/GameWorld.hpp"
#include "worlds/LobbyListWorld.hpp"
#include "worlds/InLobbyWorld.hpp"
#include "worlds/SettingsWorld.hpp"

#include "components/OpacityChanger.hpp"
#include "components/Rectangle.hpp"
#include "components/Transform.hpp"
#include "components/Sprite.hpp"
#include "components/Input.hpp"
#include "components/Button.hpp"
#include "components/Text.hpp"
#include "components/Camera.hpp"
#include "components/Event.hpp"

#include "LeaveLobbyDatagram.hpp"
#include "LeaveGameDatagram.hpp"

bool rtype::systems::SFMLSystem::sigintCaught = false;

rtype::systems::SFMLSystem::SFMLSystem(const std::string &name, unsigned int width, unsigned int height)
: System("SFML System"), _window(sf::VideoMode(width, height), name.c_str()), _event()
{
    _window.setFramerateLimit(60);
    signal(SIGINT, &rtype::systems::SFMLSystem::signalHandler);
}

void rtype::systems::SFMLSystem::onInit()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    worldManager.addWorld(new rtype::worlds::GameWorld("Game World"));
    worldManager.addWorld(new rtype::worlds::MenuWorld("Menu World"));
    worldManager.addWorld(new rtype::worlds::SettingsWorld("Settings World"));
    worldManager.addWorld(new rtype::worlds::LobbyListWorld("Lobby List World"));
    worldManager.addWorld(new rtype::worlds::InLobbyWorld("In Lobby World"));
    worldManager.changeWorld("Menu World");
}

void rtype::systems::SFMLSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;

    if (_window.isOpen()) {
        if (sigintCaught) {
            handleDisconnection();
            onClose();
        }
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                handleDisconnection();
                onClose();
            }
            events();
        }
        _window.clear();

        update(elapsedTimeAsSecond);
        render();

        _window.display();
    }
}

void rtype::systems::SFMLSystem::onClose()
{
    setState(ecs::systems::STOPPED);
    _window.close();
}

sf::RenderWindow &rtype::systems::SFMLSystem::getWindow()
{
    return _window;
}

void rtype::systems::SFMLSystem::render()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Sprite"}), [this](ecs::entities::Entity *entities) {
        auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));

        _window.draw(sprite->getSprite());
    });
    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Text"}),[this](ecs::entities::Entity *entities) {
        auto text = dynamic_cast<rtype::components::Text *>(entities->getComponent("Text"));

        _window.draw(text->getText());
    });
}

void rtype::systems::SFMLSystem::update(float elapsedTime)
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto componentsVectorForUpdatePosition = std::vector<std::string>({"Sprite", "Transform"});

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForUpdatePosition, [](ecs::entities::Entity *entities) {
        auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));
        auto transform = dynamic_cast<rtype::components::Transform *>(entities->getComponent("Transform"));

        sprite->setPosition(transform->getPosition().x, transform->getPosition().y);
        sprite->getSprite().setScale(transform->getScale().x, transform->getScale().y);
    });

    auto componentsVectorForUpdatePositionInput = std::vector<std::string>({"Text", "Transform"});
    worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForUpdatePositionInput, [](ecs::entities::Entity *entities) {
        auto text = dynamic_cast<rtype::components::Text *>(entities->getComponent("Text"));
        auto transform = dynamic_cast<rtype::components::Transform *>(entities->getComponent("Transform"));

        text->setPosition(transform->getPosition().x, transform->getPosition().y);
    });

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Input", "Text"}), [](ecs::entities::Entity *entity) {
        auto text = dynamic_cast<rtype::components::Text *>(entity->getComponent("Text"));
        auto input = dynamic_cast<rtype::components::Input *>(entity->getComponent("Input"));

        text->setString(input->getCurrentInput());
    });

    auto componentsVectorForOpacityChanger = std::vector<std::string>({"Sprite", "OpacityChanger"});

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForOpacityChanger, [elapsedTime](ecs::entities::Entity *entities) {
        auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));
        auto opacityChanger = dynamic_cast<rtype::components::OpacityChanger *>(entities->getComponent("OpacityChanger"));

        if (sprite->getOpacity() < opacityChanger->getEnd())
            sprite->setOpacity(sprite->getOpacity() + (opacityChanger->getSpeed() * elapsedTime));
    });

    auto componentsVectorForOpacityChangerText = std::vector<std::string>({"Text", "OpacityChanger"});
    worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForOpacityChangerText, [elapsedTime](ecs::entities::Entity *entities) {
        auto text = dynamic_cast<rtype::components::Text *>(entities->getComponent("Text"));
        auto opacityChanger = dynamic_cast<rtype::components::OpacityChanger *>(entities->getComponent("OpacityChanger"));

        if (text->getOpacity() < opacityChanger->getEnd())
            text->setOpacity(text->getOpacity() + (opacityChanger->getSpeed() * elapsedTime));
    });

    auto componentsVectorForButtons = std::vector<std::string>({"Sprite", "Rectangle", "Button"});

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForButtons, [](ecs::entities::Entity *entities) {
        auto rectangle = dynamic_cast<rtype::components::Rectangle *>(entities->getComponent("Rectangle"));
        auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));

        sprite->getSprite().setTextureRect(sf::IntRect(rectangle->getLeft(), rectangle->getTop(), rectangle->getWidth(), rectangle->getHeight()));
    });

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Sprite", "Rectangle"}), [](ecs::entities::Entity *entities) {
        auto rectangle = dynamic_cast<rtype::components::Rectangle *>(entities->getComponent("Rectangle"));
        auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));

        sprite->getSprite().setTextureRect(sf::IntRect(rectangle->getLeft(), rectangle->getTop(), rectangle->getWidth(), rectangle->getHeight()));
    });

    worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Camera"}), [this, elapsedTime](ecs::entities::Entity *entity) {
        auto camera = dynamic_cast<rtype::components::Camera *>(entity->getComponent("Camera"));

        camera->move(10.0f * elapsedTime, 0);
        _window.setView(camera->getCamera());
    });
}

void rtype::systems::SFMLSystem::events()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();
    auto componentsVectorForButtons = std::vector<std::string>({"Sprite", "Rectangle", "Button"});

    if (_event.type == sf::Event::MouseMoved) {
        rtype::commons::Vector2<int> cursorPos(
                _window.mapPixelToCoords(sf::Mouse::getPosition(_window)).x,
                _window.mapPixelToCoords(sf::Mouse::getPosition(_window)).y
                );

        worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForButtons, [&cursorPos](ecs::entities::Entity *entities) {
            auto rectangle = dynamic_cast<rtype::components::Rectangle *>(entities->getComponent("Rectangle"));
            auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));

            if (sprite->getSprite().getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
                rectangle->setTop(rectangle->getHeight() * 1);
            } else {
                rectangle->setTop(0);
            }
        });
    }

    if (_event.type == sf::Event::MouseButtonPressed) {
        rtype::commons::Vector2<int> cursorPos(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)).x, _window.mapPixelToCoords(sf::Mouse::getPosition(_window)).y);

        worldManager.getCurrentWorld()->getEntityManager().applyToEach(componentsVectorForButtons, [&cursorPos](ecs::entities::Entity *entities) {
            auto rectangle = dynamic_cast<rtype::components::Rectangle *>(entities->getComponent("Rectangle"));
            auto sprite = dynamic_cast<rtype::components::Sprite *>(entities->getComponent("Sprite"));
            auto button = dynamic_cast<rtype::components::Button *>(entities->getComponent("Button"));

            if (sprite->getSprite().getGlobalBounds().contains(cursorPos.x, cursorPos.y)) {
                rectangle->setTop(rectangle->getHeight() * 2);
                button->getCallback()();
            } else {
                rectangle->setTop(0);
            }
        });
    }

    if (_event.type == sf::Event::TextEntered) {
        worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Input"}),
                                                                       [this](ecs::entities::Entity *entities) {
            auto input = dynamic_cast<rtype::components::Input *>(entities->getComponent("Input"));

            if ((_event.text.unicode > 47 && _event.text.unicode < 58) || _event.text.unicode == 46) {
                input->newInput(_event.text.unicode);
            } else if (_event.text.unicode == 8) {
                input->deleteLastCharacter();
            } else if (_event.text.unicode == 10 || _event.text.unicode == 13)
                input->getCallback()();
        });
    }

    movementInput();
}

void rtype::systems::SFMLSystem::movementInput()
{
    auto &worldManager = rtype::worlds::WorldManager::getInstance();

    if (_event.type == sf::Event::KeyPressed) {
        switch (_event.key.code) {
            case sf::Keyboard::Up:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("UP_PRESS")();
                });
                break;
            case sf::Keyboard::Left:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("LEFT_PRESS")();
                });
                break;
            case sf::Keyboard::Right:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("RIGHT_PRESS")();
                });
                break;
            case sf::Keyboard::Down:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("DOWN_PRESS")();
                });
                break;
            case sf::Keyboard::Space:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("ACTION_PRESS")();
                });
                break;
            default:
                break;
        }
    }

    if (_event.type == sf::Event::KeyReleased) {
        switch (_event.key.code) {
            case sf::Keyboard::Up:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("UP_RELEASE")();
                });
                break;
            case sf::Keyboard::Left:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("LEFT_RELEASE")();
                });
                break;
            case sf::Keyboard::Right:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("RIGHT_RELEASE")();
                });
                break;
            case sf::Keyboard::Down:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("DOWN_RELEASE")();
                });
                break;
            case sf::Keyboard::Space:
                worldManager.getCurrentWorld()->getEntityManager().applyToEach(std::vector<std::string>({"Event"}), [](ecs::entities::Entity *entities) {
                    auto event = dynamic_cast<rtype::components::Event *>(entities->getComponent("Event"));

                    event->getSpecificCallback("ACTION_RELEASE")();
                });
                break;
            default:
                break;
        }
    }
}

void rtype::systems::SFMLSystem::signalHandler(int signal)
{
    sigintCaught = true;
}

void rtype::systems::SFMLSystem::handleDisconnection()
{
    auto worldName = rtype::worlds::WorldManager::getInstance().getCurrentWorld()->getWorldName();
    auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));
    if (worldName == "In Lobby World") {
        rtype::network::LeaveLobbyDatagram lld;
        lld.createLeaveLobbyDatagram(networkSystem->getUserId(), networkSystem->getLobbyId());
        networkSystem->send(lld);
    } else if (worldName == "Game World") {
        rtype::network::LeaveGameDatagram lgd;
        lgd.createLeaveGameDatagram(networkSystem->getUserId(), networkSystem->getLobbyId());
        networkSystem->send(lgd);
    }
}
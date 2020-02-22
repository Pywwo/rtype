
/* Created by Romain FOUYER on 06/11/2019 at 13:38. */

#include "systems/SystemManager.hpp"
#include "InputDatagram.hpp"

#include "systems/NetworkSystem.hpp"

#include "worlds/GameWorld.hpp"

#include "components/Sprite.hpp"
#include "components/Transform.hpp"
#include "components/Controller.hpp"
#include "components/Rectangle.hpp"
#include "components/Animator.hpp"
#include "components/Camera.hpp"
#include "components/Parallax.hpp"
#include "components/Sound.hpp"
#include "components/Timer.hpp"
#include "components/Event.hpp"
#include "components/Status.hpp"
#include "components/Score.hpp"
#include "components/Text.hpp"

#include "utilities/AssetsManager.hpp"
#include "utilities/EntityLoader.hpp"
#include "utilities/GameSettings.hpp"
#include "utilities/GameWrapper.hpp"

rtype::worlds::GameWorld::GameWorld(const std::string &name)
: World(name)
{

}

rtype::worlds::GameWorld::~GameWorld() = default;

void rtype::worlds::GameWorld::initGame()
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();
    auto &gameSettings = rtype::utils::GameSettings::getInstance();

    _entityManager.createEntity("background");
    _entityManager.createEntity("camera");
    _entityManager.createEntity("event");
    _entityManager.createEntity("background_music");

    initEvents();

    auto backgroundMusicEntity = _entityManager.getEntityByName("background_music");
    backgroundMusicEntity->assignComponent("Sound", new rtype::components::Sound(*backgroundMusicEntity, assetsManager["game_music"], rtype::components::SoundType::MUSIC));

    auto cameraEntity = _entityManager.getEntityByName("camera");
    cameraEntity->assignComponent("Camera", new rtype::components::Camera(*cameraEntity, rtype::commons::Vector2<float>(50,  (gameSettings.getHeight() / 3) / 2), 0.25f));
    auto cameraComponent = dynamic_cast<rtype::components::Camera *>(cameraEntity->getComponent("Camera"));
    cameraComponent->setSize(gameSettings.getWidth() / 3, gameSettings.getHeight() / 3);

    cameraEntity->assignComponent("Score", new rtype::components::Score(*cameraEntity));
    cameraEntity->assignComponent("Text", new rtype::components::Text(*cameraEntity, 12, assetsManager["menu_font"]));
    cameraEntity->assignComponent("Transform", new rtype::components::Transform(*cameraEntity));

    auto scoreText = dynamic_cast<rtype::components::Text *>(cameraEntity->getComponent("Text"));
    scoreText->setColor(sf::Color::White);

    auto scoreTransform = dynamic_cast<rtype::components::Transform *>(cameraEntity->getComponent("Transform"));
    scoreTransform->setPosition(cameraComponent->getCenter().x, cameraComponent->getCenter().y);

    auto backgroundEntity = _entityManager.getEntityByName("background");

    backgroundEntity->assignComponent("Sprite", new rtype::components::Sprite(*backgroundEntity, assetsManager["game_background"]));
    backgroundEntity->assignComponent("Transform", new rtype::components::Transform(*backgroundEntity));
    backgroundEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*backgroundEntity, 0, 0, 100000, 1000));
    backgroundEntity->assignComponent("Parallax", new rtype::components::Parallax(*backgroundEntity, 100));
    auto backgroundSpriteComponent = dynamic_cast<rtype::components::Sprite *>(backgroundEntity->getComponent("Sprite"));
    auto backgroundTransformComponent = dynamic_cast<rtype::components::Transform *>(backgroundEntity->getComponent("Transform"));
    backgroundTransformComponent->setPosition(-50, -100);
    backgroundSpriteComponent->setRepeated(true);
}

void rtype::worlds::GameWorld::endGame()
{
    _entityManager.deleteAllEntities();
}

void rtype::worlds::GameWorld::initEvents()
{
    auto networkSystem = dynamic_cast<rtype::systems::NetworkSystem *>(rtype::utils::GameWrapper::getInstance().getSystemManager().getSystem("Network System"));
    auto eventEntity = _entityManager.getEntityByName("event");

    eventEntity->assignComponent("Event", new rtype::components::Event(*eventEntity));

    auto eventComponent = dynamic_cast<rtype::components::Event *>(eventEntity->getComponent("Event"));

    // KEY PRESS

    eventComponent->addEvent("UP_PRESS", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_UP, rtype::RtypeKeyState::KEY_PRESSED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("DOWN_PRESS", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_DOWN, rtype::RtypeKeyState::KEY_PRESSED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("LEFT_PRESS", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_LEFT, rtype::RtypeKeyState::KEY_PRESSED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("RIGHT_PRESS", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_RIGHT, rtype::RtypeKeyState::KEY_PRESSED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("ACTION_PRESS", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_SHOOT, rtype::RtypeKeyState::KEY_PRESSED);
        networkSystem->send(id);
    });

    // KEY RELEASE

    eventComponent->addEvent("UP_RELEASE", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_UP, rtype::RtypeKeyState::KEY_RELEASED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("DOWN_RELEASE", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_DOWN, rtype::RtypeKeyState::KEY_RELEASED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("LEFT_RELEASE", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_LEFT, rtype::RtypeKeyState::KEY_RELEASED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("RIGHT_RELEASE", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_RIGHT, rtype::RtypeKeyState::KEY_RELEASED);
        networkSystem->send(id);
    });
    eventComponent->addEvent("ACTION_RELEASE", [networkSystem]() {
        rtype::network::InputDatagram id;

        id.createInputDatagram(networkSystem->getUserId(), networkSystem->getLobbyId(), rtype::RtypeGameKeys::KEY_SHOOT, rtype::RtypeKeyState::KEY_RELEASED);
        networkSystem->send(id);
    });
}

void rtype::worlds::GameWorld::initEntity(rtype::ComponentInfos &componentInfos)
{
    auto cameraEntity = _entityManager.getEntityByName("camera");
    auto cameraComponent = dynamic_cast<rtype::components::Camera *>(cameraEntity->getComponent("Camera"));

    auto &assetsManager = rtype::utils::AssetsManager::getInstance();

    _entityManager.createEntity(componentInfos.entityName);

    auto entity = _entityManager.getEntityByName(componentInfos.entityName);

    entity->assignComponent("Sprite", new rtype::components::Sprite(*entity, assetsManager[componentInfos.entityName]));
    entity->assignComponent("Transform", new rtype::components::Transform(*entity));
    entity->assignComponent("Controller", new rtype::components::Controller(*entity, 100));
    entity->assignComponent("Rectangle", new rtype::components::Rectangle(*entity, 0, 0, 32, 32));
    entity->assignComponent("Animator", new rtype::components::Animator(*entity));
    entity->assignComponent("Status", new rtype::components::Status(*entity));

    auto spriteComponent = dynamic_cast<rtype::components::Sprite *>(entity->getComponent("Sprite"));

    spriteComponent->getSprite().setOrigin(16, 16);
    auto animatorComponent = dynamic_cast<rtype::components::Animator *>(entity->getComponent("Animator"));
    animatorComponent->addAnimation("UP", rtype::components::Animator::Animation(3, 4));
    animatorComponent->addAnimation("DOWN", rtype::components::Animator::Animation(1, 0));
    animatorComponent->addAnimation("IDLE", rtype::components::Animator::Animation(2, 2));
    animatorComponent->setCurrentAnimation("IDLE");

    auto transformComponent = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
    transformComponent->setPosition(cameraComponent->getSize().x * componentInfos.position.first / 100, cameraComponent->getSize().y * componentInfos.position.second / 100);
}

void rtype::worlds::GameWorld::addEffect(rtype::components::Effect::EffectType type, rtype::commons::Vector2<float> position)
{
    static int id = 0;

    _entityManager.createEntity("explosion" + std::to_string(id));
    auto effectEntity = _entityManager.getEntityByName("explosion" + std::to_string(id));
    effectEntity->assignComponent("Effect", new rtype::components::Effect(*effectEntity, type));
    auto effectComponent = dynamic_cast<rtype::components::Effect *>(effectEntity->getComponent("Effect"));
    effectEntity->assignComponent("Sound", new rtype::components::Sound(*effectEntity, effectComponent->getSoundEffect(), rtype::components::SoundType::EFFECT));
    effectEntity->assignComponent("Sprite", new rtype::components::Sprite(*effectEntity, effectComponent->getAsset()));
    effectEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*effectEntity, 0, 0, 32, 32));
    effectEntity->assignComponent("Animator", new rtype::components::Animator(*effectEntity));
    effectEntity->assignComponent("Transform", new rtype::components::Transform(*effectEntity));
    auto spriteComponent = dynamic_cast<rtype::components::Sprite *>(effectEntity->getComponent("Sprite"));
    spriteComponent->getSprite().setOrigin(16, 16);
    auto transformComponent = dynamic_cast<rtype::components::Transform *>(effectEntity->getComponent("Transform"));
    transformComponent->setPosition(position.x, position.y);
    auto animatorComponent = dynamic_cast<rtype::components::Animator *>(effectEntity->getComponent("Animator"));
    animatorComponent->addAnimation("EFFECT", rtype::components::Animator::Animation(0, effectComponent->getAnimationNumber(), false, 0.08));
    animatorComponent->setCurrentAnimation("EFFECT");
    effectEntity->assignComponent("Timer", new rtype::components::Timer(*effectEntity,  0.6));
    id++;
}

void rtype::worlds::GameWorld::shooting(const std::string &name)
{
    auto &assetsManager = rtype::utils::AssetsManager::getInstance();

    _entityManager.createEntity(name);
    auto effectEntity = _entityManager.getEntityByName(name);
    effectEntity->assignComponent("Sprite", new rtype::components::Sprite(*effectEntity, assetsManager["basic_shoot"]));
    effectEntity->assignComponent("Rectangle", new rtype::components::Rectangle(*effectEntity, 0, 0, 32, 32));
    effectEntity->assignComponent("Animator", new rtype::components::Animator(*effectEntity));
    effectEntity->assignComponent("Transform", new rtype::components::Transform(*effectEntity));
    effectEntity->assignComponent("Controller", new rtype::components::Controller(*effectEntity, 250));
    effectEntity->assignComponent("Status", new rtype::components::Status(*effectEntity));
    effectEntity->assignComponent("Sound", new rtype::components::Sound(*effectEntity, assetsManager["shoot"], rtype::components::SoundType::EFFECT));

    auto animatorComponent = dynamic_cast<rtype::components::Animator *>(effectEntity->getComponent("Animator"));
    animatorComponent->addAnimation("SHOOT", rtype::components::Animator::Animation(0, 3, false, 0.15));
    animatorComponent->setCurrentAnimation("SHOOT");
    effectEntity->assignComponent("Timer", new rtype::components::Timer(*effectEntity,  1));
}
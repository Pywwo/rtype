/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** MonsterSystem
*/

#include "MonsterSystem.hpp"

rtype::systems::MonsterSystem::MonsterSystem(const std::string &name, ecs::managers::EntityManager &entityManager, const int windowWidth, const int windowHeight)
: System(name), _entityManager(entityManager), _nbEnemy(0), _windowWidth(windowWidth), _windowHeight(windowHeight), _rd(), _gen(_rd()), _dis(0, 100), _elapsedTimeAsSecondSinceBegin(0)
{
}

void rtype::systems::MonsterSystem::onInit()
{

}

void rtype::systems::MonsterSystem::createRandomMonster(const float &elapsedTimeAsSecond)
{
    int random = _dis(_gen) % 4;
    int nbPlayers = 0;

    _entityManager.applyToEach(std::vector<std::string>({"Transform", "Controller"}), [&nbPlayers](ecs::entities::Entity *entity) {
        if (entity->getName().find("player") != std::string::npos) {
            nbPlayers++;
        }
    });
    if (random == 0) {
        int posY =  _windowHeight / 2;
        int posX = 0;
        int inc = 32;
        int positionNormalized = -1;
        for (int i = 0; i < 5 + (nbPlayers * 1.5) + (elapsedTimeAsSecond / 10); i++) {
            createMonster(posX, posY, static_cast<rtype::Enemy>(random + 1), -100 - 25 * (elapsedTimeAsSecond / 10 + 1), 30 * positionNormalized, 10);
            posY += inc;
            if (posY >= _windowHeight) {
                posY -= inc;
                inc *= -1;
                positionNormalized *= -1;
            }
            if (posY < 0) {
                inc *= -1;
                posY += inc;
                positionNormalized *= -1;
            }
            posX += 32;
        }
    }
    if (random == 1) {
        int posY = _dis(_gen) % _windowHeight;
        int posX = 0;
        for (int i = 0; i < 1 + nbPlayers + (elapsedTimeAsSecond / 20); i++) {
            createMonster(0, posY, static_cast<rtype::Enemy>(random + 1), -250 - 30 * (elapsedTimeAsSecond / 10 + 1), 0, 100);
            posY = _dis(_gen) % _windowHeight;
            posX += 40;
        }
    }
    if (random == 2) {
        int posY = _dis(_gen) % _windowHeight;
        int posX = 0;
        for (int i = 0; i < 1; i++) {
            createMonster(0, posY, static_cast<rtype::Enemy>(random + 1), -100 - 25 * (elapsedTimeAsSecond / 15 + 1), 0, 30);
            posX += 40;
            posY = _dis(_gen) % _windowHeight;
        }
    }
    if (random == 3) {
        int posY = 0;
        int posX = 0;
        for (int i = 0; i < 1 + (nbPlayers * 1.5) + (elapsedTimeAsSecond / 20 + 1); i++) {
            createMonster(0, posY, static_cast<rtype::Enemy>(random + 1), -30, 0, 80 + 20 * (elapsedTimeAsSecond / 15 + 1));
            posX += 100;
        }
    }
}

void rtype::systems::MonsterSystem::onUpdate(float elapsedTime)
{
    float elapsedTimeAsSecond = elapsedTime / 1000000000.0f;
    static float curTime = 0;

    if (curTime > 4) {
        createRandomMonster(_elapsedTimeAsSecondSinceBegin);
        curTime = 0;
    }

    std::pair<float, float> farPlayerPos(-1, -1);

    _entityManager.applyToEach(std::vector<std::string>({"Transform", "Controller"}), [&farPlayerPos](ecs::entities::Entity *entity) {
        if (entity->getName().find("player") != std::string::npos) {
            auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
            if (farPlayerPos.first < transform->getPosition().x)
                farPlayerPos = std::make_pair(transform->getPosition().x, transform->getPosition().y);
        }
    });

    _entityManager.applyToEach(std::vector<std::string>({"Monster", "Transform", "Controller"}), [this, farPlayerPos](ecs::entities::Entity *entity) {
        auto monster = dynamic_cast<rtype::components::Monster *>(entity->getComponent("Monster"));
        auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
        auto controller = dynamic_cast<rtype::components::Controller *>(entity->getComponent("Controller"));

        if (monster->getId() == ENEMY_ONE) {
            if (transform->getPosition().y >= _windowHeight || transform->getPosition().y <= 0) {
                controller->setVelocity(rtype::commons::Vector2<float>(controller->getVelocity().x, controller->getVelocity().y * -1));
            }
        }
        if (monster->getId() == ENEMY_THREE) {
            if (farPlayerPos.second < transform->getPosition().y)
                controller->setVelocity(rtype::commons::Vector2<float>(controller->getVelocity().x, -controller->getSpeed()));
            else if (farPlayerPos.second > transform->getPosition().y)
                controller->setVelocity(rtype::commons::Vector2<float>(controller->getVelocity().x, controller->getSpeed()));
        }
        if (monster->getId() == ENEMY_FOUR) {
            if (farPlayerPos.first + _windowWidth / 3 > transform->getPosition().x) {
                controller->setVelocity(rtype::commons::Vector2<float>(controller->getVelocity().x, controller->getSpeed()));
            }
        }

    });
    curTime += elapsedTimeAsSecond;
    _elapsedTimeAsSecondSinceBegin += elapsedTimeAsSecond;
}

void rtype::systems::MonsterSystem::onClose()
{

}

void rtype::systems::MonsterSystem::createMonster(float intervalPos, float posY, const Enemy &enemyId, float velocityX, float velocityY, float speed)
{
    std::string nameEnemy = "enemy";
    float biggestPlayerPosition = 0;

    std::string tmpEnemy(nameEnemy + std::to_string(_nbEnemy));
    _entityManager.createEntity(tmpEnemy);
    auto enemyEntity = _entityManager.getEntityByName(tmpEnemy);
    enemyEntity->assignComponent("Transform", new rtype::components::Transform(*enemyEntity));
    enemyEntity->assignComponent("Controller", new rtype::components::Controller(*enemyEntity, speed));
    enemyEntity->assignComponent("Status", new rtype::components::Status(*enemyEntity));
    enemyEntity->assignComponent("Monster", new rtype::components::Monster(*enemyEntity, enemyId));
    enemyEntity->assignComponent("BoxCollider", new rtype::components::BoxCollider(*enemyEntity, rtype::commons::Vector2<float>{32, 32}));
    enemyEntity->assignComponent("Damager", new rtype::components::Damager(*enemyEntity, *enemyEntity, true));

    auto enemyController = dynamic_cast<rtype::components::Controller *>(enemyEntity->getComponent("Controller"));
    enemyController->setVelocity(rtype::commons::Vector2<float>(velocityX, velocityY));


    std::pair<float, float> farPlayerPos(-1, -1);

    _entityManager.applyToEach(std::vector<std::string>({"Transform", "Controller"}), [&farPlayerPos](ecs::entities::Entity *entity) {
        if (entity->getName().find("player") != std::string::npos) {
            auto transform = dynamic_cast<rtype::components::Transform *>(entity->getComponent("Transform"));
            if (farPlayerPos.first < transform->getPosition().x)
                farPlayerPos = std::make_pair(transform->getPosition().x, transform->getPosition().y);
        }
    });
    biggestPlayerPosition = farPlayerPos.first;
    auto enemyTransform = dynamic_cast<rtype::components::Transform *>(enemyEntity->getComponent("Transform"));
    enemyTransform->setPosition(biggestPlayerPosition + intervalPos + _windowWidth, posY);
    _nbEnemy++;
}

extern "C"
{
    #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        __declspec(dllexport)
    #endif
    rtype::systems::MonsterSystem *createSystem(ecs::managers::EntityManager &entityManager)
    {
        return new rtype::systems::MonsterSystem("Monster system", entityManager);
    }
}
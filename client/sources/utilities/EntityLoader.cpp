
/* Created by Romain FOUYER on 11/11/2019 at 14:36. */


#include <iostream>

#include "utilities/EntityLoader.hpp"
#include "components/Sprite.hpp"

rtype::utils::EntityLoader::EntitiesArguments rtype::utils::EntityLoader::entitiesArguments = {
        {rtype::utils::ComponentsHandled::SPRITE, "Sprite", {"texture"}}
};

rtype::utils::EntityLoader &rtype::utils::EntityLoader::getInstance()
{
    static rtype::utils::EntityLoader el;

    return el;
}

void rtype::utils::EntityLoader::loadEntityToWorld(rtype::worlds::World &world, const std::string &jsonData)
{
    std::stringstream ss;

    ss << jsonData;

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(ss, pt);

    world.getEntityManager().createEntity(pt.get<std::string>("name"));

    auto newEntity = world.getEntityManager().getEntityByName(pt.get<std::string>("name"));
    std::vector<std::string> arguments;

    for (auto &it : pt.get_child("components")) {
        auto &node = it.second;
        auto componentName = node.get("name", "");

        auto args = getArguments(componentName, node.get_child("arguments"));

        addComponent(newEntity, componentName, args);
    }
}

std::map<std::string, std::string> rtype::utils::EntityLoader::getArguments(const std::string &componentName, boost::property_tree::ptree &arguments) const
{
    std::map<std::string, std::string> finalArguments;

    for (auto &components : entitiesArguments) {
        if (std::get<1>(components) == componentName) {
            for (auto &wantedArgs : std::get<2>(components)) {
                finalArguments[wantedArgs] = arguments.get(wantedArgs, "");
            }
        }
    }
    return finalArguments;
}

void rtype::utils::EntityLoader::addComponent(ecs::entities::Entity *entity, const std::string &componentName, std::map<std::string, std::string> arguments)
{
    for (auto &components : entitiesArguments) {
        if (std::get<1>(components) == componentName) {
            switch (std::get<0>(components)) {
                case SPRITE:
                    entity->assignComponent(componentName, new rtype::components::Sprite(*entity, arguments["texture"]));
                    break;
            }
        }
    }
}

#ifndef SNEK_IO_ENTITY_HPP
#define SNEK_IO_ENTITY_HPP

#include <memory>
#include <SFML/Graphics.hpp>

namespace snek {

    class entity {

    public:

        virtual ~entity() = default;

        virtual void update(const sf::Time& delta_time) = 0;

        virtual void draw(sf::RenderTarget& target) const = 0;

        [[nodiscard]] virtual const sf::Vector2f& get_position() const = 0;

        virtual void set_position(float x, float y) = 0;

        void set_position(const sf::Vector2f& position) { set_position(position.x, position.y); }

        void move(const sf::Vector2f& offset) { set_position(get_position() + offset); }
    };

    template<typename T>
    concept HasBounds = requires(T t) {
        t.getGlobalBounds();
        t.getLocalBounds();
        static_cast<sf::FloatRect>(t.getGlobalBounds());
        static_cast<sf::FloatRect>(t.getLocalBounds());
    };

    template<HasBounds T> requires std::is_base_of_v<sf::Drawable, T> and std::is_base_of_v<sf::Transformable, T>
    class basic_entity : public entity {

        T object;

    public:

        template<typename... Args>
        explicit basic_entity(Args&& ... args) : object(std::forward<Args>(args)...) {}

        void update(const sf::Time& delta_time) override {}

        void draw(sf::RenderTarget& target) const override { target.draw(object); }

        [[nodiscard]] const sf::Vector2f& get_position() const override { return object.getPosition(); }

        void set_position(float x, float y) override { object.setPosition({x, y}); }

        [[nodiscard]] sf::Vector2f center() {
            const auto bounds = object.getLocalBounds();
            return {bounds.width / 2, bounds.height / 2};
        }

        T* operator->() { return &object; }
    };

    template<typename T, typename... Args>
    std::shared_ptr<basic_entity<T>> make_entity(Args&& ... args) {
        return std::make_shared<basic_entity<T>>(std::forward<Args>(args)...);
    }
}

#endif //SNEK_IO_ENTITY_HPP

#ifndef SNAKE_GAME_BASIC_STATE_HPP
#define SNAKE_GAME_BASIC_STATE_HPP

template <typename Entity>
class BasicState {
public:
    virtual ~BasicState() = default;

    virtual void enter(Entity *) = 0;

    virtual void exit(Entity *) = 0;

    virtual void execute(Entity *) = 0;
};

#endif //SNAKE_GAME_BASIC_STATE_HPP

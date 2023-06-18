#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"
using namespace std;
Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
    state->get_legal_actions();
    Move move=state->legal_actions[0];
    auto actions = state->legal_actions;
    
    int value;
    switch (state->player){
    case 0:
        value=INT_MIN;
        for(Move it:actions){
            int next_value=minimax(state->next_state(it),depth-1);
            if(value<next_value){
                value=next_value;
                move=it;
            }
        }return move;
    case 1:
        value=INT_MAX;
        for(Move it:actions){
            int next_value=minimax(state->next_state(it),depth-1);
            if(value>next_value){
                value=next_value;
                move=it;
            }
        }return move;
    // default:
    //     std::cout<<"envo";
    //     return move;
    }
}
int Minimax::minimax(State *state, int depth){
    if(!state->legal_actions.size())
    state->get_legal_actions();

    auto actions = state->legal_actions;
    
    if(!depth||state->legal_actions.empty())
        return state->evaluate();
    int value;
    switch (state->player){
    case 0:
        value=INT_MIN;
        for(Move it:actions)
            value=max(value,minimax(state->next_state(it),depth-1));
        return value;
    case 1:
        value=INT_MAX;
        for(Move it:actions)
            value=min(value,minimax(state->next_state(it),depth-1));
        return value;
    }
}
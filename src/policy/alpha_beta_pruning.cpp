#include <cstdlib>

#include "../state/state.hpp"
#include "./alpha_beta_pruning.hpp"
using namespace std;
Move Alpha_beta_pruning::get_move(State *state, int depth){
    if(!state->legal_actions.size())
    state->get_legal_actions();
    Move move=state->legal_actions[0];
    auto actions = state->legal_actions;
    
    int value;
    switch (state->player){
    case 0:
        value=INT_MIN;
        for(Move it:actions){
            int next_value=alpha_beta_pruning(state->next_state(it),depth-1,INT_MIN,INT_MAX);
            if(value<next_value){
                value=next_value;
                move=it;
            }
        }return move;
    case 1:
        value=INT_MAX;
        for(Move it:actions){
            int next_value=alpha_beta_pruning(state->next_state(it),depth-1,INT_MIN,INT_MAX);
            if(value>next_value){
                value=next_value;
                move=it;
            }
        }return move;
    }
}
int Alpha_beta_pruning::alpha_beta_pruning(State *state, int depth, int alpha, int beta){
    if(!state->legal_actions.size())
    state->get_legal_actions();

    auto actions = state->legal_actions;
    
    if(!depth||state->legal_actions.empty())
        return state->evaluate();
    switch (state->player){
    case 0:
        for(Move it:actions){
            alpha=max(alpha,alpha_beta_pruning(state->next_state(it),depth-1,alpha,beta));
            if(alpha>=beta) break;
        }return alpha;
    case 1:
        for(Move it:actions){
            beta=min(beta,alpha_beta_pruning(state->next_state(it),depth-1,alpha,beta));
            if(alpha>=beta) break;
        }return beta;
    }
}
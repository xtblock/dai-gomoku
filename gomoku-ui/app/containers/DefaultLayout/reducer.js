/*
 * ContactReducer
 *
 * The reducer takes care of our data. Using actions, we can change our
 * application state.
 * To add a new action, add it to the switch statement in the reducer function
 *
 * Example:
 * case YOUR_ACTION_CONSTANT:
 *   return state.set('yourStateVariable', true);
 */
import produce from 'immer';

// The initial state of the App
export const initialState = {

};

/* eslint-disable default-case, no-param-reassign */
const defaultLayoutReducer = (state = initialState, action) =>
  produce(state, draft => {
    switch (action.type) {
      default:
        //return state;
    }
  });

export default defaultLayoutReducer;

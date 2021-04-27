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

import {
  CHANGE_STATUS,
  CHANGE_KEYWORD,
  CHANGE_PAGE_NUMBER,
  CHANGE_NUMBER_PER_PAGE,
} from './constants';

// The initial state of the App
export const initialState = {
  status: '',
  keyword: '',
  pageNumber: '',
  numberPerPage: '',
};

/* eslint-disable default-case, no-param-reassign */
const homeReducer = (state = initialState, action) =>
  produce(state, draft => {
    switch (action.type) {
      case CHANGE_STATUS:
        // Delete all special characters
        draft.status = action.status;
        break;
      case CHANGE_KEYWORD:
        // Delete all special characters
        draft.keyword = action.keyword;
        break;
      case CHANGE_PAGE_NUMBER:
        // Delete all special characters
        draft.pageNumber = action.pageNumber;
        break;
      case CHANGE_NUMBER_PER_PAGE:
        // Delete all special characters
        draft.numberPerPage = action.numberPerPage;
        break;
      default:
        return state;
    }
  });

export default homeReducer;

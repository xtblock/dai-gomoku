/*
 * Home Actions
 *
 * Actions change things in your application
 * Since this boilerplate uses a uni-directional data flow, specifically redux,
 * we have these actions which are the only way your application interacts with
 * your application state. This guarantees that your state is up to date and nobody
 * messes it up weirdly somewhere.
 *
 * To add a new Action:
 * 1) Import your constant
 * 2) Add a function like this:
 *    export function yourAction(var) {
 *        return { type: YOUR_ACTION_CONSTANT, var: var }
 *    }
 */

import {
  CHANGE_STATUS,
  CHANGE_KEYWORD,
  CHANGE_PAGE_NUMBER,
  CHANGE_NUMBER_PER_PAGE,
} from './constants';

/**
 * Changes the input field of the form
 *
 * @param  {name} status The new text of the input field
 *
 * @return {object}    An action object with a type of CHANGE_STATUS
 */

export function changeStatus(status) {
  return {
    type: CHANGE_STATUS,
    status,
  };
}

/**
 * Changes the input field of the form
 *
 * @param  {name} keyword The new text of the input field
 *
 * @return {object}    An action object with a type of CHANGE_KEYWORD
 */

export function changeKeyword(keyword) {
  return {
    type: CHANGE_KEYWORD,
    keyword,
  };
}

/**
 * Changes the input field of the form
 *
 * @param  {name} pageNumber The new text of the input field
 *
 * @return {object}    An action object with a type of CHANGE_PAGE_NUMBER
 */

export function changePageNumber(pageNumber) {  
  return {
    type: CHANGE_PAGE_NUMBER,
    pageNumber,
  };
}

/**
 * Changes the input field of the form
 *
 * @param  {name} numberPerPage The new text of the input field
 *
 * @return {object}    An action object with a type of CHANGE_NUMBER_PER_PAGE
 */

export function changeNumberPerPage(numberPerPage) {
  return {
    type: CHANGE_NUMBER_PER_PAGE,
    numberPerPage,
  };
}

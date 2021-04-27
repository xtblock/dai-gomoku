/**
 * Homepage selectors
 */

import { createSelector } from 'reselect';
import { initialState } from './reducer';

const selectHome = state => state.home || initialState;

const makeSelectStatus = () =>
  createSelector(
    selectHome,
    homeState => homeState.status,
  );

const makeSelectKeyword = () =>
  createSelector(
    selectHome,
    homeState => homeState.keyword,
  );

const makeSelectPageNumber = () =>
  createSelector(
    selectHome,
    homeState => homeState.pageNumber,
  );

const makeSelectNumberPerPage = () =>
  createSelector(
    selectHome,
    homeState => homeState.numberPerPage,
  );

export {
  selectHome,
  makeSelectStatus,
  makeSelectKeyword,
  makeSelectPageNumber,
  makeSelectNumberPerPage,
};

/**
 * Gets the repositories of the user from Github
 */

import { call, put, select, takeLatest } from 'redux-saga/effects';
import { GET_PORTFOLIO_LIST } from 'containers/App/constants';
import { getPortfolioListSuccess, getPortfolioListError } from 'containers/App/actions';

import request from 'utils/request';
import {
  makeSelectStatus,
  makeSelectKeyword,
  makeSelectPageNumber,
  makeSelectNumberPerPage,
} from 'containers/HomePage/selectors';

import { API_SERVER_URL, API_PORTFOLIO_LIST } from 'utils/constants';

/**
 * Send contact request/response handler
 */
export function* getPortfolioList() {
  const status = yield select(makeSelectStatus());
  const keyword = yield select(makeSelectKeyword());
  const pageNumber = yield select(makeSelectPageNumber());
  const numberPerPage = yield select(makeSelectNumberPerPage());

  const requestURL = API_SERVER_URL + API_PORTFOLIO_LIST;
  try {
    // Call our request helper (see 'utils/request')
    const getPortfolioListResult = yield call(request, requestURL, {
      method: 'POST',
      body: JSON.stringify({
        status,
        keyword,
        pageNumber,
        numberPerPage,
      }),
      headers: {
        Authorization:
          'Basic ZTF1emU5ck1INWpjX2k4UHlPdGZmXzBXV05vYTpBbno3WV9CWkR2VWV0aWRiQ0hNMndLVTFsajBh',
        'Cache-Control': 'no-cache',
        'Content-Type': 'application/json; charset=utf-8',
        Accept: 'application/json',
        device_id: '123456789123456795',
        language_id: 'en',
      },
    });

    yield put(getPortfolioListSuccess(getPortfolioListResult));
  } catch (err) {
    yield put(getPortfolioListError(err));
  }
}

/**
 * Root saga manages watcher lifecycle
 */
export default function* getPortfolioListData() {
  // Watches for SEND_CONTACT actions and calls adminGetPortfolioListData when one comes in.
  // By using `takeLatest` only the result of the latest API call is applied.
  // It returns task descriptor (just like fork) so we can continue execution
  // It will be cancelled automatically on component unmount
  yield takeLatest(GET_PORTFOLIO_LIST, getPortfolioList);
}

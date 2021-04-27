/**
 * Gets the repositories of the user from Github
 */

import { call, put, select, takeLatest } from 'redux-saga/effects';
import { ADMIN_LOGIN } from 'containers/App/constants';

import request from 'utils/request';

/**
 * Send contact request/response handler
 */
export function* defaultLayout() {
 
}

/**
 * Root saga manages watcher lifecycle
 */
export default function* defaultLayoutData() {
  // Watches for SEND_CONTACT actions and calls adminLoginData when one comes in.
  // By using `takeLatest` only the result of the latest API call is applied.
  // It returns task descriptor (just like fork) so we can continue execution
  // It will be cancelled automatically on component unmount
  yield takeLatest(ADMIN_LOGIN, defaultLayout);
}

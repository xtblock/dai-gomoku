/**
 * The global state selectors
 */

import { createSelector } from 'reselect';
import { initialState } from './reducer';

const selectGlobal = state => state.global || initialState;

const selectRouter = state => state.router;

const makeSelectCurrentUser = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.currentUser,
  );

const makeSelectLoading = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.loading,
  );

const makeSelectError = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.error,
  );

/*
Admin Login
*/

const makeSelectAdminLoginResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminLoginResult,
  );

const makeSelectLoadingAdminLogin = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminLogin,
  );

const makeSelectErrorAdminLogin = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminLogin,
  );


/*
Portfolio Submit
*/

const makeSelectPortfolioSubmitResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.portfolioSubmitResult,
  );

const makeSelectLoadingPortfolioSubmit = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingPortfolioSubmit,
  );

const makeSelectErrorPortfolioSubmit = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorPortfolioSubmit,
  );

/*
Admin get Portfolio list
*/
const makeSelectAdminGetPortfolioListResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminGetPortfolioListResult,
  );

const makeSelectLoadingAdminGetPortfolioList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminGetPortfolioList,
  );

const makeSelectErrorAdminGetPortfolioList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminGetPortfolioList,
  );

/*
Admin get Portfolio detail
*/

const makeSelectAdminGetPortfolioDetailResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminGetPortfolioDetailResult,
  );

const makeSelectLoadingAdminGetPortfolioDetail = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminGetPortfolioDetail,
  );

const makeSelectErrorAdminGetPortfolioDetail = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminGetPortfolioDetail,
  );


/*
Admin get tech news list
*/

const makeSelectAdminGetTechNewsListResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminGetTechNewsListResult,
  );

const makeSelectLoadingAdminGetTechNewsList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminGetTechNewsList,
  );

const makeSelectErrorAdminGetTechNewsList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminGetTechNewsList,
  );


/*
Admin get tech news detail
*/

const makeSelectAdminGetTechNewsDetailResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminGetTechNewsDetailResult,
  );

const makeSelectLoadingAdminGetTechNewsDetail = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminGetTechNewsDetail,
  );

const makeSelectErrorAdminGetTechNewsDetail = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminGetTechNewsDetail,
  );

/*
Tech News Submit
*/

const makeSelectTechNewsSubmitResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.techNewsSubmitResult,
  );

const makeSelectLoadingTechNewsSubmit = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingTechNewsSubmit,
  );

const makeSelectErrorTechNewsSubmit = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorTechNewsSubmit,
  );


/*
Admin get blog list
*/

const makeSelectAdminGetBlogListResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminGetBlogListResult,
  );

const makeSelectLoadingAdminGetBlogList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminGetBlogList,
  );

const makeSelectErrorAdminGetBlogList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminGetBlogList,
  );


/*
Admin get blog detail
*/

const makeSelectAdminGetBlogDetailResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.adminGetBlogDetailResult,
  );

const makeSelectLoadingAdminGetBlogDetail = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingAdminGetBlogDetail,
  );

const makeSelectErrorAdminGetBlogDetail = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorAdminGetBlogDetail,
  );

/*
Blog Submit
*/

const makeSelectBlogSubmitResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.blogSubmitResult,
  );

const makeSelectLoadingBlogSubmit = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingBlogSubmit,
  );

const makeSelectErrorBlogSubmit = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorBlogSubmit,
  );

/*
Get Portfolio list
*/

const makeSelectGetPortfolioListResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.getPortfolioListResult,
  );

const makeSelectLoadingGetPortfolioList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingGetPortfolioList,
  );

const makeSelectErrorGetPortfolioList = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorGetPortfolioList,
  );
/*
Register IP
*/
const makeSelectRegisterIpResult = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.registerIpResult,
  );

const makeSelectLoadingRegisterIp = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.loadingRegisterIp,
  );

const makeSelectErrorRegisterIp = () =>
  createSelector(
    selectGlobal,
    globalState => globalState.userData.errorRegisterIp,
  );

const makeSelectLocation = () =>
  createSelector(
    selectRouter,
    routerState => routerState.location,
  );

export {
  selectGlobal,
  makeSelectCurrentUser,
  makeSelectLoading,
  makeSelectError,
  // Admin login
  makeSelectAdminLoginResult,
  makeSelectLoadingAdminLogin,
  makeSelectErrorAdminLogin,
  // Admin get Portfolio list
  makeSelectAdminGetPortfolioListResult,
  makeSelectLoadingAdminGetPortfolioList,
  makeSelectErrorAdminGetPortfolioList,
  // Admin get Portfolio detail
  makeSelectAdminGetPortfolioDetailResult,
  makeSelectLoadingAdminGetPortfolioDetail,
  makeSelectErrorAdminGetPortfolioDetail,
  // Portfolio submit
  makeSelectPortfolioSubmitResult,
  makeSelectLoadingPortfolioSubmit,
  makeSelectErrorPortfolioSubmit,
  // Admin get tech news list
  makeSelectAdminGetTechNewsListResult,
  makeSelectLoadingAdminGetTechNewsList,
  makeSelectErrorAdminGetTechNewsList,
  // Admin get tech news detail
  makeSelectAdminGetTechNewsDetailResult,
  makeSelectLoadingAdminGetTechNewsDetail,
  makeSelectErrorAdminGetTechNewsDetail,
  // Tech News Submit
  makeSelectTechNewsSubmitResult,
  makeSelectLoadingTechNewsSubmit,
  makeSelectErrorTechNewsSubmit,
  // Admin get blog list
  makeSelectAdminGetBlogListResult,
  makeSelectLoadingAdminGetBlogList,
  makeSelectErrorAdminGetBlogList,
  // Admin get blog detail
  makeSelectAdminGetBlogDetailResult,
  makeSelectLoadingAdminGetBlogDetail,
  makeSelectErrorAdminGetBlogDetail,
  // Blog Submit
  makeSelectBlogSubmitResult,
  makeSelectLoadingBlogSubmit,
  makeSelectErrorBlogSubmit,
  // Get Portfolio list
  makeSelectGetPortfolioListResult,
  makeSelectLoadingGetPortfolioList,
  makeSelectErrorGetPortfolioList,
  // Register IP
  makeSelectRegisterIpResult,
  makeSelectLoadingRegisterIp,
  makeSelectErrorRegisterIp,
  makeSelectLocation,
};

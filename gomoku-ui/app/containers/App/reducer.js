/*
 * AppReducer
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
  // Admin login
  ADMIN_LOGIN,
  ADMIN_LOGIN_SUCCESS,
  ADMIN_LOGIN_ERROR,
  // Admin get portfolio list
  ADMIN_GET_PORTFOLIO_LIST,
  ADMIN_GET_PORTFOLIO_LIST_SUCCESS,
  ADMIN_GET_PORTFOLIO_LIST_ERROR,
  // Admin get portfolio detail
  ADMIN_GET_PORTFOLIO_DETAIL,
  ADMIN_GET_PORTFOLIO_DETAIL_SUCCESS,
  ADMIN_GET_PORTFOLIO_DETAIL_ERROR,
  // Portfolio submit
  PORTFOLIO_SUBMIT,
  PORTFOLIO_SUBMIT_SUCCESS,
  PORTFOLIO_SUBMIT_ERROR,
  // Admin get tech news list
  ADMIN_GET_TECH_NEWS_LIST,
  ADMIN_GET_TECH_NEWS_LIST_SUCCESS,
  ADMIN_GET_TECH_NEWS_LIST_ERROR,
  // Admin get tech news detail
  ADMIN_GET_TECH_NEWS_DETAIL,
  ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS,
  ADMIN_GET_TECH_NEWS_DETAIL_ERROR,
  // Tech news submit
  TECH_NEWS_SUBMIT,
  TECH_NEWS_SUBMIT_SUCCESS,
  TECH_NEWS_SUBMIT_ERROR,
  // Admin get blog list
  ADMIN_GET_BLOG_LIST,
  ADMIN_GET_BLOG_LIST_SUCCESS,
  ADMIN_GET_BLOG_LIST_ERROR,
  // Admin get blog detail
  ADMIN_GET_BLOG_DETAIL,
  ADMIN_GET_BLOG_DETAIL_SUCCESS,
  ADMIN_GET_BLOG_DETAIL_ERROR,
  // Blog submit
  BLOG_SUBMIT,
  BLOG_SUBMIT_SUCCESS,
  BLOG_SUBMIT_ERROR,
  // Get portfolio list
  GET_PORTFOLIO_LIST,
  GET_PORTFOLIO_LIST_SUCCESS,
  GET_PORTFOLIO_LIST_ERROR,
  // Register Ip
  REGISTER_IP,
  REGISTER_IP_SUCCESS,
  REGISTER_IP_ERROR,
} from './constants';

export const initialState = {
  loading: false,
  error: false,
  currentUser: false,
  userData: {
    // Admin login
    adminLoginResult: null,
    loadingAdminLogin: false,
    errorAdminLogin: false,
    // Admin get portfolio list
    adminGetPortfolioListResult: null,
    loadingAdminGetPortfolioList: false,
    errorAdminGetPortfolioList: false,
    // Admin get portfolio detail
    adminGetPortfolioDetailResult: null,
    loadingAdminGetPortfolioDetail: false,
    errorAdminGetPortfolioDetail: false,
    // Portfolio Submit
    portfolioSubmitResult: null,
    loadingPortfolioSubmit: false,
    errorPortfolioSubmit: false,
    // Admin get tech news list
    adminGetTechNewsListResult: null,
    loadingAdminGetTechNewsList: false,
    errorAdminGetTechNewsList: false,
    // Admin get tech news detail
    adminGetTechNewsDetailResult: null,
    loadingAdminGetTechNewsDetail: false,
    errorAdminGetTechNewsDetail: false,
    // Tech News Submit
    techNewsSubmitResult: null,
    loadingTechNewsSubmit: false,
    errorTechNewsSubmit: false,
    // Admin get blog list
    adminGetBlogListResult: null,
    loadingAdminGetBlogList: false,
    errorAdminGetBlogList: false,
    // Admin get blog detail
    adminGetBlogDetailResult: null,
    loadingAdminGetBlogDetail: false,
    errorAdminGetBlogDetail: false,
    // Blog Submit
    blogSubmitResult: null,
    loadingBlogSubmit: false,
    errorBlogSubmit: false,
    // Get portfolio list
    getPortfolioListResult: null,
    loadingGetPortfolioList: false,
    errorGetPortfolioList: false,
    // Register IP
    registerIpResult: null,
    loadingRegisterIp: false,
    errorRegisterIp: false,
  },
};

const appReducer = (state = initialState, action) =>
  produce(state, draft => {
    switch (action.type) {
      // Admin login
      case ADMIN_LOGIN:
        draft.userData.loadingAdminLogin = true;
        draft.userData.errorAdminLogin = false;
        draft.userData.adminLoginResult = null;
        break;
      case ADMIN_LOGIN_SUCCESS:
        draft.userData.adminLoginResult = action.adminLoginResult;
        draft.userData.loadingAdminLogin = false;
        draft.userData.errorAdminLogin = false;
        break;
      case ADMIN_LOGIN_ERROR:
        draft.userData.adminLoginResult = null;
        draft.userData.loadingAdminLogin = false;
        draft.userData.errorAdminLogin = true;
        break;
      // Admin Get Portfolio list
      case ADMIN_GET_PORTFOLIO_LIST:
        draft.userData.loadingAdminGetPortfolioList = true;
        draft.userData.errorAdminGetPortfolioList = false;
        draft.userData.adminGetPortfolioListResult = null;
        break;
      case ADMIN_GET_PORTFOLIO_LIST_SUCCESS:
        draft.userData.adminGetPortfolioListResult = action.adminGetPortfolioListResult;
        draft.userData.loadingAdminGetPortfolioList = false;
        draft.userData.errorAdminGetPortfolioList = false;
        break;
      case ADMIN_GET_PORTFOLIO_LIST_ERROR:
        draft.userData.adminGetPortfolioListResult = null;
        draft.userData.loadingAdminGetPortfolioList = false;
        draft.userData.errorAdminGetPortfolioList = true;
        break;
      // Admin Get Portfolio detail
      case ADMIN_GET_PORTFOLIO_DETAIL:
        draft.userData.loadingAdminGetPortfolioDetail = true;
        draft.userData.errorAdminGetPortfolioDetail = false;
        draft.userData.adminGetPortfolioDetailResult = null;
        break;
      case ADMIN_GET_PORTFOLIO_DETAIL_SUCCESS:
        draft.userData.adminGetPortfolioDetailResult = action.adminGetPortfolioDetailResult;
        draft.userData.loadingAdminGetPortfolioDetail = false;
        draft.userData.errorAdminGetPortfolioDetail = false;
        break;
      case ADMIN_GET_PORTFOLIO_DETAIL_ERROR:
        draft.userData.adminGetPortfolioDetailResult = null;
        draft.userData.loadingAdminGetPortfolioDetail = false;
        draft.userData.errorAdminGetPortfolioDetail = true;
        break;
      // Portfolio Submit
      case PORTFOLIO_SUBMIT:
        draft.userData.loadingPortfolioSubmit = true;
        draft.userData.errorPortfolioSubmit = false;
        draft.userData.portfolioSubmitResult = null;
        break;
      case PORTFOLIO_SUBMIT_SUCCESS:
        draft.userData.portfolioSubmitResult = action.portfolioSubmitResult;
        draft.userData.loadingPortfolioSubmit = false;
        draft.userData.errorPortfolioSubmit = false;
        break;
      case PORTFOLIO_SUBMIT_ERROR:
        draft.userData.portfolioSubmitResult = null;
        draft.userData.loadingPortfolioSubmit = false;
        draft.userData.errorPortfolioSubmit = true;
        break;
      // Admin Get tech news list
      case ADMIN_GET_TECH_NEWS_LIST:
        draft.userData.loadingAdminGetTechNewsList = true;
        draft.userData.errorAdminGetTechNewsList = false;
        draft.userData.adminGetTechNewsListResult = null;
        break;
      case ADMIN_GET_TECH_NEWS_LIST_SUCCESS:
        draft.userData.adminGetTechNewsListResult = action.adminGetTechNewsListResult;
        draft.userData.loadingAdminGetTechNewsList = false;
        draft.userData.errorAdminGetTechNewsList = false;
        break;
      case ADMIN_GET_TECH_NEWS_LIST_ERROR:
        draft.userData.adminGetTechNewsListResult = null;
        draft.userData.loadingAdminGetTechNewsList = false;
        draft.userData.errorAdminGetTechNewsList = true;
        break;
      // Admin Get tech news detail
      case ADMIN_GET_TECH_NEWS_DETAIL:
        draft.userData.loadingAdminGetTechNewsDetail = true;
        draft.userData.errorAdminGetTechNewsDetail = false;
        draft.userData.adminGetTechNewsDetailResult = null;
        break;
      case ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS:
        draft.userData.adminGetTechNewsDetailResult = action.adminGetTechNewsDetailResult;
        draft.userData.loadingAdminGetTechNewsDetail = false;
        draft.userData.errorAdminGetTechNewsDetail = false;
        break;
      case ADMIN_GET_TECH_NEWS_DETAIL_ERROR:
        draft.userData.adminGetTechNewsDetailResult = null;
        draft.userData.loadingAdminGetTechNewsDetail = false;
        draft.userData.errorAdminGetTechNewsDetail = true;
        break;
      // Tech News Submit
      case TECH_NEWS_SUBMIT:
        draft.userData.loadingTechNewsSubmit = true;
        draft.userData.errorTechNewsSubmit = false;
        draft.userData.techNewsSubmitResult = null;
        break;
      case TECH_NEWS_SUBMIT_SUCCESS:
        draft.userData.techNewsSubmitResult = action.techNewsSubmitResult;
        draft.userData.loadingTechNewsSubmit = false;
        draft.userData.errorTechNewsSubmit = false;
        break;
      case TECH_NEWS_SUBMIT_ERROR:
        draft.userData.techNewsSubmitResult = null;
        draft.userData.loadingTechNewsSubmit = false;
        draft.userData.errorTechNewsSubmit = true;
        break;
      // Admin Get blog list
      case ADMIN_GET_BLOG_LIST:
        draft.userData.loadingAdminGetBlogList = true;
        draft.userData.errorAdminGetBlogList = false;
        draft.userData.adminGetBlogListResult = null;
        break;
      case ADMIN_GET_BLOG_LIST_SUCCESS:
        draft.userData.adminGetBlogListResult = action.adminGetBlogListResult;
        draft.userData.loadingAdminGetBlogList = false;
        draft.userData.errorAdminGetBlogList = false;
        break;
      case ADMIN_GET_BLOG_LIST_ERROR:
        draft.userData.adminGetBlogListResult = null;
        draft.userData.loadingAdminGetBlogList = false;
        draft.userData.errorAdminGetBlogList = true;
        break;
      // Admin Get blog detail
      case ADMIN_GET_BLOG_DETAIL:
        draft.userData.loadingAdminGetBlogDetail = true;
        draft.userData.errorAdminGetBlogDetail = false;
        draft.userData.adminGetBlogDetailResult = null;
        break;
      case ADMIN_GET_BLOG_DETAIL_SUCCESS:
        draft.userData.adminGetBlogDetailResult = action.adminGetBlogDetailResult;
        draft.userData.loadingAdminGetBlogDetail = false;
        draft.userData.errorAdminGetBlogDetail = false;
        break;
      case ADMIN_GET_BLOG_DETAIL_ERROR:
        draft.userData.adminGetBlogDetailResult = null;
        draft.userData.loadingAdminGetBlogDetail = false;
        draft.userData.errorAdminGetBlogDetail = true;
        break;
      // Blog Submit
      case BLOG_SUBMIT:
        draft.userData.loadingBlogSubmit = true;
        draft.userData.errorBlogSubmit = false;
        draft.userData.blogSubmitResult = null;
        break;
      case BLOG_SUBMIT_SUCCESS:
        draft.userData.blogSubmitResult = action.blogSubmitResult;
        draft.userData.loadingBlogSubmit = false;
        draft.userData.errorBlogSubmit = false;
        break;
      case BLOG_SUBMIT_ERROR:
        draft.userData.blogSubmitResult = null;
        draft.userData.loadingBlogSubmit = false;
        draft.userData.errorBlogSubmit = true;
        break;
        // Get Portfolio list
      case GET_PORTFOLIO_LIST:
        draft.userData.loadingGetPortfolioList = true;
        draft.userData.errorGetPortfolioList = false;
        draft.userData.getPortfolioListResult = null;
        break;
      case GET_PORTFOLIO_LIST_SUCCESS:
        draft.userData.getPortfolioListResult = action.getPortfolioListResult;
        draft.userData.loadingGetPortfolioList = false;
        draft.userData.errorGetPortfolioList = false;
        break;
      case GET_PORTFOLIO_LIST_ERROR:
        draft.userData.getPortfolioListResult = null;
        draft.userData.loadingGetPortfolioList = false;
        draft.userData.errorGetPortfolioList = true;
        break;
      // Register IP
      case REGISTER_IP:
        draft.userData.loadingRegisterIp = true;
        draft.userData.errorRegisterIp = false;
        draft.userData.registerIpResult = null;
        break;
      case REGISTER_IP_SUCCESS:
        draft.userData.registerIpResult = action.registerIpResult;
        draft.userData.loadingRegisterIp = false;
        draft.userData.errorRegisterIp = false;
        break;
      case REGISTER_IP_ERROR:
        draft.userData.registerIpResult = null;
        draft.userData.loadingRegisterIp = false;
        draft.userData.errorRegisterIp = true;
        break;
    }
  });
export default appReducer;

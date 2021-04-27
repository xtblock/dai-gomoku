/*
 * App Actions
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
  //Admin Login
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

  //Portfolio submit
  PORTFOLIO_SUBMIT,
  PORTFOLIO_SUBMIT_SUCCESS,
  PORTFOLIO_SUBMIT_ERROR,
  // Admin get tech news list
  ADMIN_GET_TECH_NEWS_LIST,
  ADMIN_GET_TECH_NEWS_LIST_SUCCESS,
  ADMIN_GET_TECH_NEWS_LIST_ERROR,
  // Admin Get Tech News detail
  ADMIN_GET_TECH_NEWS_DETAIL,
  ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS,
  ADMIN_GET_TECH_NEWS_DETAIL_ERROR,
  // Tech news submit
  TECH_NEWS_SUBMIT,
  TECH_NEWS_SUBMIT_SUCCESS,
  TECH_NEWS_SUBMIT_ERROR,
  // Admin Get Blog list
  ADMIN_GET_BLOG_LIST,
  ADMIN_GET_BLOG_LIST_SUCCESS,
  ADMIN_GET_BLOG_LIST_ERROR,
  // Admin Get Blog detail
  ADMIN_GET_BLOG_DETAIL,
  ADMIN_GET_BLOG_DETAIL_SUCCESS,
  ADMIN_GET_BLOG_DETAIL_ERROR,
  // Blog submit
  BLOG_SUBMIT,
  BLOG_SUBMIT_SUCCESS,
  BLOG_SUBMIT_ERROR,
  // Get Portfolio list
  GET_PORTFOLIO_LIST,
  GET_PORTFOLIO_LIST_SUCCESS,
  GET_PORTFOLIO_LIST_ERROR,
  // Register IP
  REGISTER_IP,
  REGISTER_IP_SUCCESS,
  REGISTER_IP_ERROR,
} from './constants';

// Admin Login
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_LOGIN
 */
export function adminLogin() {
  return {
    type: ADMIN_LOGIN,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminLoginResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_LOGIN_SUCCESS passing the repos
 */
export function adminLoginSuccess(adminLoginResult) {
  return {
    type: ADMIN_LOGIN_SUCCESS,
    adminLoginResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_LOGIN_ERROR passing the error
 */
export function adminLoginError(error) {
  return {
    type: ADMIN_LOGIN_ERROR,
    error,
  };
}


// Admin get Portfolio list
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_GET_PORTFOLIO_LIST
 */
export function adminGetPortfolioList() {
  return {
    type: ADMIN_GET_PORTFOLIO_LIST,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminGetPortfolioListResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_GET_PORTFOLIO_LIST_SUCCESS passing the repos
 */
export function adminGetPortfolioListSuccess(adminGetPortfolioListResult) {
  return {
    type: ADMIN_GET_PORTFOLIO_LIST_SUCCESS,
    adminGetPortfolioListResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_GET_PORTFOLIO_LIST_ERROR passing the error
 */
export function adminGetPortfolioListError(error) {
  return {
    type: ADMIN_GET_PORTFOLIO_LIST_ERROR,
    error,
  };
}

// Admin get Portfolio detail
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_GET_PORTFOLIO_DETAIL
 */
export function adminGetPortfolioDetail() {
  return {
    type: ADMIN_GET_PORTFOLIO_DETAIL,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminGetPortfolioDetailResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_GET_PORTFOLIO_DETAIL_SUCCESS passing the repos
 */
export function adminGetPortfolioDetailSuccess(adminGetPortfolioDetailResult) {
  return {
    type: ADMIN_GET_PORTFOLIO_DETAIL_SUCCESS,
    adminGetPortfolioDetailResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_GET_PORTFOLIO_DETAIL_ERROR passing the error
 */
export function adminGetPortfolioDetailError(error) {
  return {
    type: ADMIN_GET_PORTFOLIO_DETAIL_ERROR,
    error,
  };
}

// Portfolio submit
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of PORTFOLIO_SUBMIT
 */
export function portfolioSubmit() {
  return {
    type: PORTFOLIO_SUBMIT,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} portfolioSubmitResult The repository data
 *
 * @return {object}      An action object with a type of PORTFOLIO_SUBMIT_SUCCESS passing the repos
 */
export function portfolioSubmitSuccess(portfolioSubmitResult) {
  return {
    type: PORTFOLIO_SUBMIT_SUCCESS,
    portfolioSubmitResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of PORTFOLIO_SUBMIT_ERROR passing the error
 */
export function portfolioSubmitError(error) {
  return {
    type: PORTFOLIO_SUBMIT_ERROR,
    error,
  };
}


// Admin get tech news list
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_GET_TECH_NEWS_LIST
 */
export function adminGetTechNewsList() {
  return {
    type: ADMIN_GET_TECH_NEWS_LIST,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminGetTechNewsListResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_GET_TECH_NEWS_LIST_SUCCESS passing the repos
 */
export function adminGetTechNewsListSuccess(adminGetTechNewsListResult) {
  return {
    type: ADMIN_GET_TECH_NEWS_LIST_SUCCESS,
    adminGetTechNewsListResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_GET_TECH_NEWS_LIST_ERROR passing the error
 */
export function adminGetTechNewsListError(error) {
  return {
    type: ADMIN_GET_TECH_NEWS_LIST_ERROR,
    error,
  };
}


// Admin get tech news detail
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_GET_TECH_NEWS_DETAIL
 */
export function adminGetTechNewsDetail() {
  return {
    type: ADMIN_GET_TECH_NEWS_DETAIL,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminGetTechNewsDetailResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS passing the repos
 */
export function adminGetTechNewsDetailSuccess(adminGetTechNewsDetailResult) {
  return {
    type: ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS,
    adminGetTechNewsDetailResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_GET_TECH_NEWS_DETAIL_ERROR passing the error
 */
export function adminGetTechNewsDetailError(error) {
  return {
    type: ADMIN_GET_TECH_NEWS_DETAIL_ERROR,
    error,
  };
}


// Tech News submit
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of TECH_NEWS_SUBMIT
 */
export function techNewsSubmit() {
  return {
    type: TECH_NEWS_SUBMIT,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} techNewsSubmitResult The repository data
 *
 * @return {object}      An action object with a type of TECH_NEWS_SUBMIT_SUCCESS passing the repos
 */
export function techNewsSubmitSuccess(techNewsSubmitResult) {
  return {
    type: TECH_NEWS_SUBMIT_SUCCESS,
    techNewsSubmitResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of TECH_NEWS_SUBMIT_ERROR passing the error
 */
export function techNewsSubmitError(error) {
  return {
    type: TECH_NEWS_SUBMIT_ERROR,
    error,
  };
}


// Admin get blog list
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_GET_BLOG_LIST
 */
export function adminGetBlogList() {
  return {
    type: ADMIN_GET_BLOG_LIST,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminGetBlogListResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_GET_BLOG_LIST_SUCCESS passing the repos
 */
export function adminGetBlogListSuccess(adminGetBlogListResult) {
  return {
    type: ADMIN_GET_BLOG_LIST_SUCCESS,
    adminGetBlogListResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_GET_BLOG_LIST_ERROR passing the error
 */
export function adminGetBlogListError(error) {
  return {
    type: ADMIN_GET_BLOG_LIST_ERROR,
    error,
  };
}


// Admin get blog detail
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of ADMIN_GET_BLOG_DETAIL
 */
export function adminGetBlogDetail() {
  return {
    type: ADMIN_GET_BLOG_DETAIL,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} adminGetBlogDetailResult The repository data
 *
 * @return {object}      An action object with a type of ADMIN_GET_BLOG_DETAIL_SUCCESS passing the repos
 */
export function adminGetBlogDetailSuccess(adminGetBlogDetailResult) {
  return {
    type: ADMIN_GET_BLOG_DETAIL_SUCCESS,
    adminGetBlogDetailResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of ADMIN_GET_BLOG_DETAIL_ERROR passing the error
 */
export function adminGetBlogDetailError(error) {
  return {
    type: ADMIN_GET_BLOG_DETAIL_ERROR,
    error,
  };
}


// Tech News submit
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of BLOG_SUBMIT
 */
export function blogSubmit() {
  return {
    type: BLOG_SUBMIT,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} blogSubmitResult The repository data
 *
 * @return {object}      An action object with a type of BLOG_SUBMIT_SUCCESS passing the repos
 */
export function blogSubmitSuccess(blogSubmitResult) {
  return {
    type: BLOG_SUBMIT_SUCCESS,
    blogSubmitResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of BLOG_SUBMIT_ERROR passing the error
 */
export function blogSubmitError(error) {
  return {
    type: BLOG_SUBMIT_ERROR,
    error,
  };
}


// Get Portfolio list
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of GET_PORTFOLIO_LIST
 */
export function getPortfolioList() {
  return {
    type: GET_PORTFOLIO_LIST,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} getPortfolioListResult The repository data
 *
 * @return {object}      An action object with a type of GET_PORTFOLIO_LIST_SUCCESS passing the repos
 */
export function getPortfolioListSuccess(getPortfolioListResult) {
  return {
    type: GET_PORTFOLIO_LIST_SUCCESS,
    getPortfolioListResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of GET_PORTFOLIO_LIST_ERROR passing the error
 */
export function getPortfolioListError(error) {
  return {
    type: GET_PORTFOLIO_LIST_ERROR,
    error,
  };
}

// Register Ip
/**
 * Load the repositories, this action starts the request saga
 *
 * @return {object} An action object with a type of REGISTER_IP
 */
export function registerIp() {
  return {
    type: REGISTER_IP,
  };
}

/**
 * Dispatched when the repositories are loaded by the request saga
 *
 * @param  {array} registerIpResult The repository data
 *
 * @return {object}      An action object with a type of REGISTER_IP_SUCCESS passing the repos
 */
export function registerIpSuccess(registerIpResult) {
  return {
    type: REGISTER_IP_SUCCESS,
    registerIpResult,
  };
}

/**
 * Dispatched when loading the repositories fails
 *
 * @param  {object} error The error
 *
 * @return {object}       An action object with a type of REGISTER_IP_ERROR passing the error
 */
export function registerIpError(error) {
  return {
    type: REGISTER_IP_ERROR,
    error,
  };
}

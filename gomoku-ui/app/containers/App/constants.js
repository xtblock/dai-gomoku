/*
 * AppConstants
 * Each action has a corresponding type, which the reducer knows and picks up on.
 * To avoid weird typos between the reducer and the actions, we save them as
 * constants here. We prefix them with 'yourproject/YourComponent' so we avoid
 * reducers accidentally picking up actions they shouldn't.
 *
 * Follow this format:
 * export const YOUR_ACTION_CONSTANT = 'yourproject/YourContainer/YOUR_ACTION_CONSTANT';
 */

// Admin Login
export const ADMIN_LOGIN = 'monnacorp/AdminLogin/ADMIN_LOGIN';
export const ADMIN_LOGIN_SUCCESS = 'monnacorp/AdminLogin/ADMIN_LOGIN_SUCCESS';
export const ADMIN_LOGIN_ERROR = 'monnacorp/AdminLogin/ADMIN_LOGIN_ERROR';

// Admin Get Portfolio list
export const ADMIN_GET_PORTFOLIO_LIST = 'monnacorp/admin/Portfolio/ADMIN_GET_PORTFOLIO_LIST';
export const ADMIN_GET_PORTFOLIO_LIST_SUCCESS = 'monnacorp/admin/Portfolio/ADMIN_GET_PORTFOLIO_LIST_SUCCESS';
export const ADMIN_GET_PORTFOLIO_LIST_ERROR = 'monnacorp/admin/Portfolio/ADMIN_GET_PORTFOLIO_LIST_ERROR';

// Admin Get Portfolio detail
export const ADMIN_GET_PORTFOLIO_DETAIL = 'monnacorp/admin/PortfolioForm/ADMIN_GET_PORTFOLIO_DETAIL';
export const ADMIN_GET_PORTFOLIO_DETAIL_SUCCESS = 'monnacorp/admin/PortfolioForm/ADMIN_GET_PORTFOLIO_DETAIL_SUCCESS';
export const ADMIN_GET_PORTFOLIO_DETAIL_ERROR = 'monnacorp/admin/PortfolioForm/ADMIN_GET_PORTFOLIO_DETAIL_ERROR';

// Portfolio submit
export const PORTFOLIO_SUBMIT = 'monnacorp/admin/PortfolioForm/PORTFOLIO_SUBMIT';
export const PORTFOLIO_SUBMIT_SUCCESS = 'monnacorp/admin/PortfolioForm/PORTFOLIO_SUBMIT_SUCCESS';
export const PORTFOLIO_SUBMIT_ERROR = 'monnacorp/admin/PortfolioForm/PORTFOLIO_SUBMIT_ERROR';
// Admin Get Tech News list
export const ADMIN_GET_TECH_NEWS_LIST = 'monnacorp/admin/TechNews/ADMIN_GET_TECH_NEWS_LIST';
export const ADMIN_GET_TECH_NEWS_LIST_SUCCESS = 'monnacorp/admin/TechNews/ADMIN_GET_TECH_NEWS_LIST_SUCCESS';
export const ADMIN_GET_TECH_NEWS_LIST_ERROR = 'monnacorp/admin/TechNews/ADMIN_GET_TECH_NEWS_LIST_ERROR';
// Admin Get Tech News detail
export const ADMIN_GET_TECH_NEWS_DETAIL = 'monnacorp/admin/TechNewsForm/ADMIN_GET_TECH_NEWS_DETAIL';
export const ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS = 'monnacorp/admin/TechNewsForm/ADMIN_GET_TECH_NEWS_DETAIL_SUCCESS';
export const ADMIN_GET_TECH_NEWS_DETAIL_ERROR = 'monnacorp/admin/TechNewsForm/ADMIN_GET_TECH_NEWS_DETAIL_ERROR';
// Tech news submit
export const TECH_NEWS_SUBMIT = 'monnacorp/admin/TechNewsForm/TECH_NEWS_SUBMIT';
export const TECH_NEWS_SUBMIT_SUCCESS = 'monnacorp/admin/TechNewsForm/TECH_NEWS_SUBMIT_SUCCESS';
export const TECH_NEWS_SUBMIT_ERROR = 'monnacorp/admin/TechNewsForm/TECH_NEWS_SUBMIT_ERROR';
// Admin Get Blog list
export const ADMIN_GET_BLOG_LIST = 'monnacorp/admin/Blog/ADMIN_GET_BLOG_LIST';
export const ADMIN_GET_BLOG_LIST_SUCCESS = 'monnacorp/admin/Blog/ADMIN_GET_BLOG_LIST_SUCCESS';
export const ADMIN_GET_BLOG_LIST_ERROR = 'monnacorp/admin/Blog/ADMIN_GET_BLOG_LIST_ERROR';

// Admin Get Blog detail
export const ADMIN_GET_BLOG_DETAIL = 'monnacorp/admin/BlogForm/ADMIN_GET_BLOG_DETAIL';
export const ADMIN_GET_BLOG_DETAIL_SUCCESS = 'monnacorp/admin/BlogForm/ADMIN_GET_BLOG_DETAIL_SUCCESS';
export const ADMIN_GET_BLOG_DETAIL_ERROR = 'monnacorp/admin/BlogForm/ADMIN_GET_BLOG_DETAIL_ERROR';

// Blog submit
export const BLOG_SUBMIT = 'monnacorp/admin/BlogForm/BLOG_SUBMIT';
export const BLOG_SUBMIT_SUCCESS = 'monnacorp/admin/BlogForm/BLOG_SUBMIT_SUCCESS';
export const BLOG_SUBMIT_ERROR = 'monnacorp/admin/BlogForm/BLOG_SUBMIT_ERROR';
// Get Portfolio list
export const GET_PORTFOLIO_LIST = 'monnacorp/Home/GET_PORTFOLIO_LIST';
export const GET_PORTFOLIO_LIST_SUCCESS = 'monnacorp/Home/GET_PORTFOLIO_LIST_SUCCESS';
export const GET_PORTFOLIO_LIST_ERROR = 'monnacorp/Home/GET_PORTFOLIO_LIST_ERROR';
// Contact
export const REGISTER_IP = 'monnacorp/RegisterIp/REGISTER_IP';
export const REGISTER_IP_SUCCESS = 'monnacorp/RegisterIp/REGISTER_IP_SUCCESS';
export const REGISTER_IP_ERROR = 'monnacorp/RegisterIp/REGISTER_IP_ERROR';

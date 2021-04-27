import HomePage from 'containers/HomePage/Loadable';

// https://github.com/ReactTraining/react-router/tree/master/packages/react-router-config
const routes = [
  {
    path: '/',
    exact: true,
    name: 'Home',
  },
  {
    path: '/home',
    exact: true,
    name: 'Home',
    component: HomePage,
  },
  {
    path: '/portfolio',
    exact: true,
    name: 'PortfolioPage',
    component: PortfolioPage,
  },
  {
    path: '/project-details/:portfolioId?',
    exact: true,
    name: 'ProjectDetailsPage',
    component: ProjectDetailsPage,
  },
  {
    path: '/tech-news',
    exact: true,
    name: 'TechNewsPage',
    component: TechNewsPage,
  },
  {
    path: '/blog',
    exact: true,
    name: 'BlogPage',
    component: BlogPage,
  },
  {
    path: '/register-ip',
    exact: true,
    name: 'RegisterIpPage',
    component: RegisterIpPage,
  },
];

export default routes;

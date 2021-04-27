import React from 'react';

const Dashboard = React.lazy(() => import('./views/Dashboard'));

// https://github.com/ReactTraining/react-router/tree/master/packages/react-router-config
const adminRoutes = [
  { path: '/admin', exact: true, name: 'Admin' },
  {
    path: '/admin/dashboard',
    exact: true,
    name: 'Dashboard',
    component: Dashboard,
  },
  {
    path: '/admin/portfolio',
    exact: true,
    name: 'Portfolio',
    component: PortfolioPage,
  },
  {
    path: '/admin/portfolio-form/:portfolioId?',
    exact: true,
    name: 'Portfolio Form',
    component: PortfolioFormPage,
  },
  {
    path: '/admin/tech-news',
    exact: true,
    name: 'Tech News',
    component: TechNewsPage,
  },
  {
    path: '/admin/tech-news-form/:techNewsId?',
    exact: true,
    name: 'Tech News Form',
    component: TechNewsFormPage,
  },
  { path: '/admin/blog', exact: true, name: 'Blog', component: BlogPage },
  {
    path: '/admin/blog-form/:blogId?',
    exact: true,
    name: 'Blog Form',
    component: BlogFormPage,
  },
];

export default adminRoutes;

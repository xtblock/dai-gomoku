/**
 *
 * App.js
 *
 * This component is the skeleton around the actual pages, and should only
 * contain code that should be seen on all pages. (e.g. navigation bar)
 *
 */

import React from 'react';
import { HashRouter, Switch, Route } from 'react-router-dom';
import GlobalStyle from '../../global-styles';
import './App.scss';

// import NotFoundPage from 'containers/NotFoundPage/Loadable';

const loading = () => (
  <div className="animated fadeIn pt-3 text-center">Loading...</div>
);

// Containers
const DefaultLayout = React.lazy(() => import('../DefaultLayout'));
const FrontEndLayout = React.lazy(() => import('../FrontEndLayout'));

// Pages

const HomePage = React.lazy(() =>
  import('../HomePage')
);

/*
const Login = React.lazy(() =>
  import('../../views/Pages/Login')
);
const Register = React.lazy(() =>
  import('../../views/Pages/Register')
);
const Page404 = React.lazy(() =>
  import('../../views/Pages/Page404')
);
const Page500 = React.lazy(() =>
  import('../../views/Pages/Page500')
);
*/

export default function App() {
  return (
    <div>
      <HashRouter>
        <React.Suspense fallback={loading()}>
          <Switch>
            {/*
            <Route exact path="/login" name="Login Page" render={props => <Login {...props} />} />
            <Route exact path="/register" name="Register Page" render={props => <Register {...props} />} />
            <Route exact path="/404" name="Page 404" render={props => <Page404 {...props} />} />
            <Route exact path="/500" name="Page 500" render={props => <Page500 {...props} />} />
            */}
            <Route
              path="/admin"
              name="Admin"
              render={props => <DefaultLayout {...props} />}
            />
            <Route
              path="/"
              name="Home"
              render={props => <HomePage {...props} />}
            />
          </Switch>
        </React.Suspense>
      </HashRouter>
      <GlobalStyle />
    </div>
  );
}

import React, { Component, Suspense } from 'react';
import { Redirect, Route, Switch } from 'react-router-dom';
import { Container } from 'reactstrap';
import PropTypes from 'prop-types';

import { AppFooter, AppHeader } from '@coreui/react';
// routes config
import routes from '../../routes';

const FrontEndFooter = React.lazy(() => import('./FrontEndFooter'));
const FrontEndHeader = React.lazy(() => import('./FrontEndHeader'));

class FrontEndLayout extends Component {
  loading = () => (
    <div className="animated fadeIn pt-1 text-center">Loading...</div>
  );

  signOut(e) {
    e.preventDefault();
    this.props.history.push('/login');
  }

  render() {
    return (
      <div className="app front-end-container">
        <AppHeader fixed className="front-end-header-wrapper">
          <Suspense fallback={this.loading()}>
            <FrontEndHeader {...this.props} onLogout={e => this.signOut(e)} />
          </Suspense>
        </AppHeader>
        <div className="app-body">
          <main className="main">
            <Container fluid>
              <Suspense fallback={this.loading()}>
                <Switch>
                  {routes.map((route, idx) => {
                    const key = `route_${idx}`;
                    if (route.component) {
                      return (
                        <Route
                          key={key}
                          path={route.path}
                          exact={route.exact}
                          name={route.name}
                          render={props => <route.component {...props} />}
                        />
                      );
                    }
                    return null;
                  })}
                  <Redirect from="/" to="/home" />
                </Switch>
              </Suspense>
            </Container>
          </main>
        </div>
        <AppFooter>
          <Suspense fallback={this.loading()}>
            <FrontEndFooter />
          </Suspense>
        </AppFooter>
      </div>
    );
  }
}

FrontEndLayout.propTypes = {
  history: PropTypes.object,
};

export default FrontEndLayout;

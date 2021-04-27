/**
 * Asynchronously loads the component for DefaultLayout
 */

import loadable from 'utils/loadable';

export default loadable(() => import('./index'));

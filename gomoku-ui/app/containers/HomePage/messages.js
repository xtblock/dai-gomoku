/*
 * HomePage Messages
 *
 * This contains all the text for the HomePage container.
 */
import { defineMessages } from 'react-intl';

export const scope = 'app.containers.HomePage';

export default defineMessages({
  header1: {
    id: `${scope}.header`,
    defaultMessage: 'Freelance Mobile Developer',
  },
  header2: {
    id: `${scope}.header`,
    defaultMessage:
      'Highly experienced in developing mobile applications using React Native',
  },
});

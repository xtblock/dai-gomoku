import localForage from 'localforage';

export const loadState = () => {
    try {
        const serializedState = localStorage.getItem('state');
        if (serializedState === null) {
            return undefined;
        }
        return JSON.parse(serializedState);
    } catch (err) {
        return undefined;
    }
};

export const saveState = (state) => {
    try {
        //const serializedState = JSON.stringify({ global: state.get('global').toJS() });
        const serializedState = JSON.stringify({ global: state.global });
        localStorage.setItem('state', serializedState);
    } catch (err) {
        console.log(err);
    }
};
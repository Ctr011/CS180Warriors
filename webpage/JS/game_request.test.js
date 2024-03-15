const { JSDOM } = require('jsdom');

// Mocking the DOM environment
const dom = new JSDOM('<!DOCTYPE html><html><body></body></html>');
const { window } = dom;
const { document } = window;

global.window = window;
global.document = document;

global.alert = jest.fn(); // Mock alert function

const game_request = require('./game_request.js');

describe('game_request', () => {
    beforeEach(() => {
        // Reset the DOM state between tests
        document.body.innerHTML = '';
    });

    test('it should send a game request and redirect to main search page if confirmed', async () => {
        // Create form elements and add them to the DOM
        const form = document.createElement('form');
        form.id = 'game_request';
        const gameNameInput = document.createElement('input');
        gameNameInput.id = 'gameName';
        gameNameInput.value = 'Test Game';
        const gameDesInput = document.createElement('input');
        gameDesInput.id = 'gameDes';
        gameDesInput.value = 'Test Description';
        form.appendChild(gameNameInput);
        form.appendChild(gameDesInput);
        document.body.appendChild(form);

        // Mock the fetch function
        global.fetch = jest.fn().mockImplementation(() => {
            return Promise.resolve({
                ok: true,
                json: () => Promise.resolve({ success: true })
            });
        });

        // Mock the confirm dialog
        global.window.confirm = jest.fn().mockReturnValue(true);

        // Mock window.location.replace
        const replaceMock = jest.fn();
        window.location.replace = replaceMock;

        // Trigger form submission
        await game_request(new Event('submit'));

        // Check if fetch was called with the correct parameters
        expect(fetch).toHaveBeenCalledWith('/add_game', {
            method: 'POST',
            body: expect.any(FormData)
        });
    });
});

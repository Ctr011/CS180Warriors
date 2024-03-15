const { JSDOM } = require('jsdom');

// Mocking the DOM environment
const dom = new JSDOM('<!DOCTYPE html><html><body></body></html>');
const { window } = dom;
const { document } = window;

global.window = window;
global.document = document;

global.alert = jest.fn(); // Mock alert function

const search_tag = require('./mainsearch.js');

describe('search_tag', () => {
    beforeEach(() => {
        // Reset the DOM state between tests
        document.body.innerHTML = '';
    });

    test('it should send a tag search request and redirect to main search page if successful', async () => {
        // Create form elements and add them to the DOM
        const form = document.createElement('form');
        form.id = 'tagsearch';
        const tagInput = document.createElement('input');
        tagInput.id = 's_tag';
        tagInput.value = 'testtag';
        form.appendChild(tagInput);
        document.body.appendChild(form);

        // Mock the fetch function
        global.fetch = jest.fn().mockResolvedValueOnce({
            status: 200
        });

        // Trigger form submission
        await search_tag(new Event('submit'));

        // Check if fetch was called with the correct parameters
        expect(fetch).toHaveBeenCalledWith('/main_tags', {
            method: 'POST',
            body: expect.any(FormData)
        });
    });

    test('it should show an alert if tag search request fails', async () => {
        // Create form elements and add them to the DOM
        const form = document.createElement('form');
        form.id = 'tagsearch';
        const tagInput = document.createElement('input');
        tagInput.id = 's_tag';
        tagInput.value = 'testtag';
        form.appendChild(tagInput);
        document.body.appendChild(form);

        // Mock the fetch function to simulate a failed request
        global.fetch = jest.fn().mockRejectedValueOnce(new Error('Network error'));

        // Trigger form submission
        await search_tag(new Event('submit'));

        // Check if fetch was called with the correct parameters
        expect(fetch).toHaveBeenCalledWith('/main_tags', {
            method: 'POST',
            body: expect.any(FormData)
        });

        // Check if alert was shown
        expect(alert).toHaveBeenCalledWith('Error: Network error\n Please Contact Technical Support!');
    });
});

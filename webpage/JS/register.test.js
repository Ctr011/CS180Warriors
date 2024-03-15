const { JSDOM } = require('jsdom');

const dom = new JSDOM('<!DOCTYPE html><html><body></body></html>');
const { window } = dom;
const { document } = window;

global.window = window;
global.document = document;

global.alert = jest.fn(); // Mock alert function

const user_register = require('./register_page');


describe('user_register function', () => {
    test('should register user successfully', async () => {
        // Mock fetch
        global.fetch = jest.fn(() => Promise.resolve({ status: 200 }));

        // Mock document and form elements
        document.body.innerHTML = `
            <form id="user_register">
                <input type="text" id="name" value="John Doe">
                <input type="text" id="username" value="john.doe@example.com">
                <input type="password" id="password" value="password123">
                <input type="password" id="re_password" value="password123">
                <button type="submit">Submit</button>
            </form>
        `;
        
        // Call user_register function
        await user_register(new Event('submit'));

        // Assert fetch call
        expect(fetch).toHaveBeenCalledWith('/register', {
            method: 'POST',
            body: expect.any(FormData)
        });

        // Wait for the asynchronous operations to complete
        await new Promise(resolve => setTimeout(resolve, 100)); // Adjust timeout if necessary
    });

    test('should show an alert for passwords mismatch', async () => {
        // Spy on window.alert
        const alertSpy = jest.spyOn(window, 'alert').mockImplementation(() => {}); // Mock window.alert
    
        // Mock document and form elements
        document.body.innerHTML = `
            <form id="user_register">
                <input type="text" id="name" value="John Doe">
                <input type="text" id="username" value="john.doe@example.com">
                <input type="password" id="password" value="password123">
                <input type="password" id="re_password" value="d"> <!-- Mismatched password -->
                <button type="submit">Submit</button>
            </form>
        `;
    
        // Call user_register function
        await user_register(new Event('submit'));
    });
    
    test('should show an alert for existing user', async () => {
        // Mock fetch
        global.fetch = jest.fn(() => Promise.resolve({ status: 0 })); // Simulate existing user (status 0)
    
        // Spy on window.alert
        const alertSpy = jest.spyOn(window, 'alert').mockImplementation(() => {}); // Mock window.alert
    
        // Mock document and form elements
        document.body.innerHTML = `
            <form id="user_register">
                <input type="text" id="name" value="John Doe">
                <input type="text" id="username" value="existing.user@example.com"> <!-- Existing username -->
                <input type="password" id="password" value="password123">
                <input type="password" id="re_password" value="password123">
                <button type="submit">Submit</button>
            </form>
        `;
    
        // Call user_register function
        await user_register(new Event('submit'));
    
        // Expect an alert to be shown with the correct message
        expect(alertSpy).toHaveBeenCalledWith("User Already Exists...");
    });    
});

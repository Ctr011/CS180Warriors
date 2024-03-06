const { JSDOM } = require('jsdom');

const dom = new JSDOM('<!DOCTYPE html><html><body></body></html>');
const { window } = dom;
const { document } = window;

global.window = window;
global.document = document;

global.alert = jest.fn(); // Mock alert function

const userlog = require('./login_page');


describe('userlog function', () => {
  test('should log in successfully', async () => {
      // Mock fetch
      global.fetch = jest.fn(() => Promise.resolve({ status: 200 }));

      // Mock window.location.replace
      const replaceMock = jest.fn();
      window.location.replace = replaceMock;

      // Mock document and form elements
      document.body.innerHTML = `
          <form id="userlog">
              <input type="text" id="username" value="testUser">
              <input type="password" id="password" value="testPassword">
              <button type="submit">Submit</button>
          </form>
      `;
      
      // Call userlog function
      await userlog(new Event('submit'));

      // Assert fetch call
      expect(fetch).toHaveBeenCalledWith('/login', {
          method: 'POST',
          body: expect.any(FormData)
      });

      // Wait for the asynchronous operations to complete
      await new Promise(resolve => setTimeout(resolve, 100)); // Adjust timeout if necessary
  });
});

describe('userlog function', () => {
  test('should show an alert for incorrect login', async () => {
      // Mock fetch
      global.fetch = jest.fn(() => Promise.resolve({ status: 401 })); // Simulate incorrect login (status 401)

      // Spy on window.alert
      const alertSpy = jest.spyOn(window, 'alert').mockImplementation(() => {}); // Mock window.alert

      // Mock document and form elements
      document.body.innerHTML = `
          <form id="userlog">
              <input type="text" id="username" value="testUser">
              <input type="password" id="password" value="testPassword">
              <button type="submit">Submit</button>
          </form>
      `;
      
      // Call userlog function
      await userlog(new Event('submit'));

      // Assert fetch call
      expect(fetch).toHaveBeenCalledWith('/login', {
          method: 'POST',
          body: expect.any(FormData)
      });

      // Assert that window.alert was called with the correct message
      expect(alertSpy).toHaveBeenCalledWith("Incorrect Login. Please Try Again...");
  });
});


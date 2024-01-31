// This is the login page Java Script File, this file will handle either sending or recieving the information.

// Setting Up Event Listener
document.addEventListener('DOMContentLoaded', (event)=>{
    const form = document.querySelector('#userlog');
    if(form){
        form.addEventListener('submit', userlog, true);
    }
});

/*
* @function userlog
* This function's main goal is to see if the user has a username and password, or if they are the same. 
*/

async function userlog(event){
    const form = event.currentTarget;
    const user_log = document.getElementById("username").value;
    const user_pass = document.getElementById("password").value;

    const formData = new FormData();
    formData.append('user', user_log);
    formData.append('user_pass', user_pass);

    try{
        const response = await fetch('/login', {
            method: 'POST',
            body: formData
        });
        const data = await response;
        console.log('SUCCESS', data);
        console.log('USERNAME: ', user_log);
        console.log("PASSWORD: ", user_pass);
    } catch(error){
        console.error('ERROR: ', error);
        alert(error + "\n Please Contact Technical Support!");
    }
    
    event.preventDefault();
}
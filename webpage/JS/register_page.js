// This is the login page Java Script File, this file will handle either sending or recieving the information.

// Setting Up Event Listener
document.addEventListener('DOMContentLoaded', (event)=>{
    const form = document.querySelector('#user_register');
    if(form){
        form.addEventListener('submit', user_register, true);
    }
});

/*
* @function userlog
* This function's main goal is to see if the user has a username and password, or if they are the same. 
*/
//we can make it toward this script alerts != passwords
async function user_register(event){
    const form = event.currentTarget;
    const user_name = document.getElementById("name").value
    const user_log = document.getElementById("username").value;
    const user_pass = document.getElementById("password").value;
    const user_pass2 = document.getElementById("re_password").value;


    const formData = new FormData();
    formData.append('user', user_log);
    formData.append('user_pass', user_pass);
    formData.append('name', user_name);
    formData.append('pass', user_pass2);
    try{
        const response = await fetch('/register', {
            method: 'POST',
            body: formData
        });
        const data = await response;
        console.log('SUCCESS', data);
        console.log('USERNAME: ', user_log);
        console.log("PASSWORD: ", user_pass);
        console.log("CONFIRM: ", user_pass2);
        if(response.status != 200){
            window.alert("Passwords do not match...");
        }
        else{
            window.location.replace("/loginindex.html");  //change the page where we are loading here
        }
    } catch(error){
        console.error('ERROR: ', error);
        alert(error + "\n Please Contact Technical Support!");
    }
    
    event.preventDefault();
}
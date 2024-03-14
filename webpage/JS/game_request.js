// This is the login page Java Script File, this file will handle either sending or recieving the information.

// Setting Up Event Listener
document.addEventListener('DOMContentLoaded', (event)=>{
    const form = document.querySelector('#game_request');
    if(form){
        form.addEventListener('submit', game_request, true);
    }
});

/*
* @function userlog
* This function's main goal is to see if the user has a username and password, or if they are the same. 
*/

async function game_request(event){
    const form = event.currentTarget;
    const game_req = document.getElementById("gameName").value;
    const sm_des = document.getElementById("gameDes").value;

    const formData = new FormData();
    formData.append('gameName', game_req);
    formData.append('gameDes', sm_des);

    try{
        const response = await fetch('/add_game', {
            method: 'POST',
            body: formData
        });
        const data = await response;
        console.log('SUCCESS', data);
        console.log('GAME: ', game_req);
        console.log("DESCRIPTION: ", sm_des);
        if(response.status != 200){
            window.alert("Cannot Send Request At This Time, Please Come Back Later...");
            window.location.replace("/mainsearch.html");
        }
        else{
            const result = window.confirm("Is This All You Want To Request?");
            if(result){
                window.location.replace("/mainsearch.html");  //change the page where we are loading here
            }
        }
    } catch(error){
        console.error('ERROR: ', error);
        alert(error + "\n Please Contact Technical Support!");
    }
    
    event.preventDefault();
}
module.exports = game_request;
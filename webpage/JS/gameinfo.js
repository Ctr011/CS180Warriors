// This is the login page Java Script File, this file will handle either sending or recieving the information.

// Setting Up Event Listener
// document.addEventListener('DOMContentLoaded', (event)=>{
//     const form = document.querySelector('#game');
//     if(form){
//         form.addEventListener('submit', game, true);
//     }
// });

/*
* @function userlog
* This function's main goal is to see if the user has a username and password, or if they are the same. 
*/

window.onload = async function game(){
    // var game_info = JSON.stringify(localStorage.getItem("game_list"));
    var game_info = JSON.parse(localStorage.getItem("game_list"));
    console.log(game_info);

    let games = document.getElementById("data_out");

    // games.innerHTML = "We Cooking..."

    let out = " ";
    // i = 0;
    for(let gamess of game_info){
        out+= `
                <ul> 
                    <h> Game Name: </h>
                    <p>${gamess.name} </p>
                    <h> Game Description: </h>
                    <p>${gamess.description}</p>
                </ul> 
        `;
    }
    // console.log(i);
    console.log(out);
    games.innerHTML = out;

}
module.exports = game_request;
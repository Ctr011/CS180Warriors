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

    let out = "";
    let maxResults = 4; // Maximum number of results
    
    // Shuffle function to shuffle the array
    function shuffle(array) {
        for (let i = array.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [array[i], array[j]] = [array[j], array[i]];
        }
        return array;
    }
    
    // Shuffle the game_info array
    const shuffledGames = shuffle(game_info);
    
    // Iterate through the shuffled array and append the first 4 results
    for (let i = 0; i < Math.min(shuffledGames.length, maxResults); i++) {
        const gamess = shuffledGames[i];
        out += `
            <ul> 
                <h> <strong>Game Name:</strong> </h>
                <p>${gamess.name}</p>
                <h> Game Description: </h>
                <p>${gamess.description}</p>
            </ul> 
        `;
    }
    
    console.log(out);
    games.innerHTML = out;
    

}
module.exports = game_request;
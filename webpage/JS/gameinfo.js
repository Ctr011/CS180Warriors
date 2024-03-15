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
    let maxResults = 20; // Maximum number of results
    
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
        <div style="border: 2px solid black; padding: 20px; margin: 20px; margin-bottom: 0px; background-color: #fbfbf6; border-radius: 10px;">
            <ul style="margin-bottom: -10px;"> 
                <h style="color: black; margin-bottom: 10px; font-size: 22px;"> <strong>Game Name:</strong> </h>
                <p style="color: black; margin-bottom: 20px; font-size: 20px;">${gamess.name}</p>
                <h style="color: black; margin-bottom: 10px; font-size: 22px;"> <strong>Game Description:</strong> </h>
                <p style="color: black; margin-bottom: 20px; font-size: 19px;">${gamess.description}</p>
            </ul> 
        </div>
        `;
    }
    
    console.log(out);
    games.innerHTML = out;
    
    games.style.display = 'flex';
    games.style.justifyContent = 'center';
    games.style.alignItems = 'center';

}
module.exports = game_request;
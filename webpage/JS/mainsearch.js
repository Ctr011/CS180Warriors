// This is the login page Java Script File, this file will handle either sending or recieving the information.

// Setting Up Event Listener
document.addEventListener('DOMContentLoaded', (event)=>{
    const form = document.querySelector('#tagsearch');
    if(form){
        form.addEventListener('submit', search_tag, true);
    }
});

/*
* @function userlog
* This function's main goal is to see if the user has a username and password, or if they are the same. 
*/

async function search_tag(event){
    const form = event.currentTarget;
    const s_tag = document.getElementById("s_tag").value;
    // const user_pass = document.getElementById("password").value;

    const formData = new FormData();
    formData.append('tags', s_tag);
    // formData.append('user_pass', user_pass);

    try{
        const response = await fetch('/main_tags', {
            method: 'POST',
            body: formData
        });
        // const m = await response;
        // const data = await response.arrayBuffer();
        // let decode = new TextDecoder('utf-16');
        const data = await response.json();
        console.log('SUCCESS', data);
        console.log('TAGS: ', s_tag);
        // console.log("PASSWORD: ", user_pass);
        localStorage.setItem("game_list", JSON.stringify(data));
        if(response.status != 200){
            window.alert("Sorry, We Currently Do Not Have This Tag...Try Writing It In A Different Manner...");
        }
        else{
            window.location.replace("/gameinfo.html");  //change the page where we are loading here
        }
    } catch(error){
        console.error('ERROR: ', error);
        alert(error + "\n Please Contact Technical Support!");
    }
    
    event.preventDefault();
}

module.exports = search_tag;

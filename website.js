const X_TURN = 1;
const O_TURN = 2;
const GAME_OVER = 3;
var turn = O_TURN;

function changeImage(str){
    let image = document.getElementById(str);
    if(!(image.hasAttribute("src"))){
        if(turn = X_TURN){
            image.src = "https://upload.wikimedia.org/wikipedia/commons/thumb/f/f6/LetterX.svg/1200px-LetterX.svg.png"
            // x image
            turn = O_TURN;
        } else if(turn = O_TURN){
            image.src = "https://upload.wikimedia.org/wikipedia/commons/thumb/f/fe/LetterO.svg/1200px-LetterO.svg.png"
            // o image
            turn = X_TURN;
        }
    }
    if(checkWin()){
        clearTicTacToe();
    }
}

function checkWin(){

}

function clearTicTacToe(){

}
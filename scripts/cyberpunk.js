
document.addEventListener('DOMContentLoaded', () => {

    showWhitePage(false);

    document.querySelector('.icone-return').addEventListener('click', async function () {
        showGates(true);
        
        await new Promise(resolve => setTimeout(resolve, 2300));
        showWhitePage(true);
        await new Promise(resolve => setTimeout(resolve, 1500));
        showGates(false);

        await new Promise(resolve => setTimeout(resolve, 1000));

        location.href = '../templates/home.html';
    })


    function showGates(bolean) {
        if (bolean) {
            gateSound()
            document.querySelector('.divine-left-gate').style.left = 0;
            document.querySelector('.divine-left-gate').style.backgroundImage = "url('../imgs/divine-left-gate.gif')";

            document.querySelector('.divine-right-gate').style.right = 0;
            document.querySelector('.divine-right-gate').style.backgroundImage = "url('../imgs/divine-right-gate.gif')";

        } else {
            document.querySelector('.divine-left-gate').style.left = '-50%';
            document.querySelector('.divine-left-gate').style.backgroundImage = "url('')";

            document.querySelector('.divine-right-gate').style.right = '-50%';
            document.querySelector('.divine-right-gate').style.backgroundImage = "url('')";
        }
    }

    async function gateSound() {
        await new Promise(resolve => setTimeout(resolve, 900));
        const cyberGateAudio = new Audio('../sounds/Cyberpunk[Sound Effect].mp3');
        cyberGateAudio.addEventListener('loadedmetadata', function () {
            cyberGateAudio.play();
        });
    }

    async function showWhitePage(bolean) {
        if (bolean) {
            document.querySelector('.tela-branca').classList.toggle('top-0');
            document.querySelector('.tela-branca').style.zIndex = 999;

        } else {
            await new Promise(resolve => setTimeout(resolve, 500));
            document.querySelector('.tela-branca').classList.toggle('top-0');

            await new Promise(resolve => setTimeout(resolve, 500));
            document.querySelector('.tela-branca').style.zIndex = 0;
        }
    }
});

document.addEventListener('DOMContentLoaded', () => {


    document.querySelector('.cyber-style').addEventListener('click', async function () {
        showGates(true);

        await new Promise(resolve => setTimeout(resolve, 3800));
        showGates(false);
        document.querySelector('.background-steampunk').style.display = 'none';
        document.querySelector('.cyberpunk-container').classList.toggle('invisible');


        await new Promise(resolve => setTimeout(resolve, 1000));
        document.querySelector('.tela-branca').style.opacity = 0;
        switchPageInfos(true);
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

    function switchPageInfos(bolean) {
        if (bolean) {
            document.title = "Cyberpunk Project";

            const newIcon = "../imgs/cyber-eye.png";
            const favicon = document.getElementById('favicon');
            favicon.href = newIcon;
        }
    }
});
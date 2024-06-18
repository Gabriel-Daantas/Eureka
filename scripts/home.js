

document.addEventListener('DOMContentLoaded', () => {


    document.querySelector('.cyber-style').addEventListener('click', async function () {
        showGates(true);

        await new Promise(resolve => setTimeout(resolve, 3800));

        showGates(false);
        document.querySelector('.background-steampunk').style.display = 'none';
    })


    function showGates(bolean) {
        if (bolean) {
            reproduzirSom()
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

    function reproduzirSom() {
        const cyberGateAudio = new Audio('../sounds/Cyberpunk[Sound Effect]');
        cyberGateAudio.addEventListener('loadedmetadata', function () {
            cyberGateAudio.play();
        });
    }
});
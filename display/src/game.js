const emory = require('emory');

const GAME_WINDOW_TITLE = "Keep Talking And Nobody Explodes";
const GAME_MONO_BASE = [GAME_WINDOW_TITLE, "mono.dll"];
const GAME_PLAYER_BASE = [GAME_WINDOW_TITLE, "UnityPlayer.dll"];

const TIMER_ADDRESS = GAME_MONO_BASE.concat(["0x00264A68", "0x30", "0xBD8", "0x20", "0x10", "0x98", "0x8", "0x8", "0x40", "0x28", "0x90"]);
const STRIKE_ADDRESS = GAME_PLAYER_BASE.concat(["0x0144CB20", "0x10", "0x440", "0x18", "0x70", "0x50", "0x60", "0x54"]);

function formatFloatTimeToStringTime(time) {
    const timer = [];
    const minute = Math.floor(time / 60);
    const second = Math.floor(time % 60);
    const milli = Math.floor(((time - (minute * 60) - second) * 100) % 100);

    if (minute >= 1) {
        if (minute < 10) {
            timer.push("0");
        }

        timer.push(minute);
        timer.push(":");

        if (second < 10) {
            timer.push("0");
        }

        timer.push(second);
    } else {
        if (second < 10) {
            timer.push("0");
        }

        timer.push(second);
        timer.push(".");

        if (milli < 10) {
            timer.push("0");
        }

        timer.push(milli);
    }

    return timer.join('');
}

function fetchKtaneInformation() {
    return {
        strikes: emory.getIntValueFrom(...STRIKE_ADDRESS),
        timer: formatFloatTimeToStringTime(emory.getFloatValueFrom(...TIMER_ADDRESS))
    };
}

module.exports.fetchKtaneInformation = fetchKtaneInformation;
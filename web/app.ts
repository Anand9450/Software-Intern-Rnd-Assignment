document.addEventListener('DOMContentLoaded', () => {
    const statsEl = document.getElementById('stats');
    if (statsEl) {
        statsEl.innerText = 'FPS: 15 (Static) | Resolution: 640x480 (Static)';
    }
});
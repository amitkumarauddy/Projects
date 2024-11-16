document.getElementById('checkBtn').addEventListener('click', () => {
    const inputText = document.getElementById('inputText').value;
    const vowels = ['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'];
    let vowelCount = 0;
    let vowelDetails = '';

    if (!inputText) {
        document.getElementById('vowelOutput').textContent = "Please enter some text.";
        return;
    }

    for (let char of inputText) {
        if (vowels.includes(char)) {
            vowelCount++;
            vowelDetails += char + ' ';
        }
    }

    const resultMessage = vowelCount
        ? `Total Vowels: ${vowelCount}\nVowels: ${vowelDetails.trim()}`
        : "No vowels found in the text.";

    document.getElementById('vowelOutput').textContent = resultMessage;
});

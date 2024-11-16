document.getElementById('calculateBtn').addEventListener('click', () => {
    const principal = parseFloat(document.getElementById('principal').value);
    const rate = parseFloat(document.getElementById('rate').value);
    const time = parseFloat(document.getElementById('time').value);
    const currency = document.getElementById('currency').value;

    if (isNaN(principal) || isNaN(rate) || isNaN(time) || principal <= 0 || rate <= 0 || time <= 0) {
        alert("Please enter valid input values.");
        return;
    }

    // Compound Interest Formula
    const maturityAmount = principal * Math.pow(1 + rate / 100, time);
    document.getElementById('output').textContent = `Your maturity amount is ${currency} ${maturityAmount.toFixed(2)}`;
});

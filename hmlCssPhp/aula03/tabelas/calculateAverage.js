const trs = document.querySelectorAll('tr');

trs.forEach((tr, index) => {
  if (index === 0) return;
  const tds = tr.querySelectorAll('td');
  const n1 = parseFloat(tds[2].textContent);
  const n2 = parseFloat(tds[3].textContent);
  const avg = (n1 + n2) / 2;
  tds[4].textContent = avg;

  if (avg >= 6) {
    tds[4].classList.add('approved');
  }
});
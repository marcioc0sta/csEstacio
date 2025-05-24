function selectHtmlById(id) {
  return document.getElementById(id);
}

const ruaInput = selectHtmlById('rua');
const bairroInput = selectHtmlById('bairro');
const cidadeInput = selectHtmlById('cidade');
const estadoInput = selectHtmlById('estado');
const complementoInput = selectHtmlById('complemento');

function removeError () {
  selectHtmlById('cep').classList.remove('error');
  selectHtmlById('hint').classList.remove('active');
}


function ValidateCep() {
  const cep = selectHtmlById('cep').value;
  const cepPattern = /^[0-9]{8}$/;

  if (!cepPattern.test(cep)) {
    selectHtmlById('cep').classList.add('error');
    selectHtmlById('hint').classList.add('active');

    return false
  }

  const correiosAPI = `https://viacep.com.br/ws/${cep}/json/`;

    fetch(correiosAPI).then(response => {
        response.json().then(data => {            
          removeError()

            if (data.erro) {
                alert('CEP não encontrado');
                return;
            }

            ruaInput.value = data.logradouro;
            bairroInput.value = data.bairro;
            cidadeInput.value = data.localidade;
            estadoInput.value = data.uf;
            complementoInput.value = data.complemento;
        });
    })

  return false
}

function clearInputs() {
  const cep = document.getElementById('cep').value;
  if (cep === '') {
    removeError()
    ruaInput.value = '';
    bairroInput.value = '';
    cidadeInput.value = '';
    estadoInput.value = '';
    complementoInput.value = '';
  }
}


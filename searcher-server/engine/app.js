
function limparResultados() {
	$("#results").empty();
}

function buscar() {
	query = $("#search-query").val();

	typeSearch = getTypeSearch();
	if (query.length == 0) {
		//alert("Por favor, informe um texto de busca!");
		return;
	}

	var find = ' ';
	var re = new RegExp(find, 'g');

	query = query.replace(re, "_");

	$.getJSON("busca.php?val="+typeSearch+"/"+query, function(result, status) {

		if (result['results']) {
			limparResultados();
			$.each(result['results'], function(i, field){
            	inserirResultado(field.title, field.url, field.snippet);
       		});
		}	
	});
}



$(document).ready(function() {

	$('#search-query').keypress(function (e) {
	  if (e.which == 13) {
	    $('#botao').click();
	    return false;
	  }
	});
});

function inserirResultado(title, url, snippet) {
	novaDiv = '<div class="row myresult">'+
            '<div class="col-md-12 myurlTitle">'+
            '  <a href="'+url+'">'+title+'</a>'+
            '</div>'+
            '<div class="col-md-12 myurl">'+
            ' '+ url+
            '</div>'+
            '<div class="col-md-12 mysnippet">'+
            '  '+snippet+
            '</div>'+
          '</div> ';

    $("#results").append(novaDiv);
}

function getTypeSearch() {
	return $('input[name=ranking]:checked').val();
}
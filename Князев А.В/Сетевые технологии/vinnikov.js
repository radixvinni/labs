/*
	Есть проблема с rowspan. Идеи как с этим бороться?
*/
window.onload = function() {
    var button_go = document.getElementById("button_go");
    button_go.onclick = function() {
        var tables = document.getElementsByTagName('table');
		for(var table=0;table<tables.length;table++){ 
			numrow=0;
			var rows = tables[table].rows;
			for(var row=0;row<rows.length;row++){
				var cells = rows[row].cells;
				cells[0].insertBefore(document.createTextNode(numrow),cells[0].firstChild);
				for(var cell=0;cell<cells.length;cell++)
				{
					cells[cell].style.backgroundColor=(cell==0?"#ffe":(cell==cells.length-1?"#eef":(cell%2==0?"#fee":"#eff")));
				}
				numrow++;
			}
		}
		return false;
    };
	var button_reload = document.getElementById("button_reload");
    button_reload.onclick = function() {
		location.reload(true);
	}
};

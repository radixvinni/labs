
//TESTS.js
function renew_tests(){
	$(".test .test-state-close").unbind('click').click(function() {
		var id=$(this).parent().attr('id').split('_')[1];
		$.post('index.php',{'ajax':1,'action':'admin_delete','id':id,'what':'test'});
		$(this).parent().fadeOut(500);
	});
	$(".test").unbind('dblclick').dblclick(function() {
		var el=$(this);
		var oldhtml=el.html();
		el.html("<form><input type='text' class='inline-edit' value='"+el.find('label').text()+"'/></form>");
		el.find("input").focus().blur(function () {
			el.html(oldhtml);
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			var id=el.attr('id').split('_')[1];
			$.post('index.php',{'ajax':1,'action':'admin_test','id':id,'val':val}, function(response) {
				el.html($(response).find('.test').html());
				renew_tests();
				renew_checkboxes();
			});
			return false;
		});
	});
}
$(function() {
	$("#tests-sortable").disableSelection().sortable({
		placeholder: "test-placeholder ui-corner-all",
		update : function(){
			var order = $('#tests-sortable').sortable('serialize');
			$.post('index.php?'+order,{'ajax':1,'action':'admin_sort','what':'test'});
		}
	});
	$(".test-add").click(function() {
		var el=$(this);
		el.html("<form><input type='text' class='inline-edit'/></form>");
		el.find("input").focus().blur(function () {
			el.html("<i>Добавить тест</i>");
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			$.post('index.php',{'ajax':1,'action':'admin_test','id':-1,'val':val}, function(response) {
				$("#tests-sortable").append($(response).find('done').html());
				el.html("<i>Добавить тест</i>");
				renew_tests();
				renew_checkboxes();
			});
			return false;
		});
	});
	renew_tests();
});

//CATEGORIES.js
function renew_cats(){
	$("#cats-sortable .test-state-close").unbind('click').click(function() {
		var id=$(this).parent().parent().attr('id').split('_')[1];
		$.post('index.php',{'ajax':1,'action':'admin_delete','id':id,'what':'cat'});
		$(this).parent().parent().fadeOut(500);
	});
	$("#cats-sortable .ui-widget-header").unbind('dblclick').dblclick(function() {
		var el=$(this);
		var oldhtml=el.html();
		el.html("<form><input type='text' class='inline-edit' value='"+el.text()+"'/></form>");
		el.find("input").focus().blur(function () {
			el.html(oldhtml);
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			var id=el.parent().attr('id').split('_')[1];
			$.post('index.php',{'ajax':1,'action':'admin_cat','id':id,'val':val}, function(response) {
				el.html($(response).find('.ui-widget-header').html());
				renew_cats();
			});
			return false;
		});
	});
	$(".theme-add").unbind('click').click(function() {
		var el=$(this);
		var cat=el.parent().attr('id').split('_')[1];
		el.html("<form><input type='text' class='inline-edit'/></form>");
		el.find("input").focus().blur(function () {
			el.html("<i style='font-weight: normal;'>Добавить тему</i>");
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			$.post('index.php',{'ajax':1,'action':'admin_theme','id':-1,'cat':cat,'val':val}, function(response) {
				el.prev().append($(response).find('done').html());
				el.html("<i>Добавить тест</i>");
				renew_themes();
			});
			return false;
		});
	});
}
$(function() {
	$("#cats-sortable").disableSelection().sortable({
		update : function(){
			var order = $('#cats-sortable').sortable('serialize');
			$.post('index.php?'+order,{'ajax':1,'action':'admin_sort','what':'cat'});
		}
	});
	$("#cat-add-header").click(function() {
		var el=$(this);
		el.html("<form><input type='text' class='inline-edit'/></form>");
		el.find("input").focus().blur(function () {
			el.html("<i style='font-weight: normal;'>Добавить предмет</i>");
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			$.post('index.php',{'ajax':1,'action':'admin_cat','id':-1,'val':val}, function(response) {
				$("#cats-sortable").append($(response).find('done').html());
				el.html("<i style='font-weight: normal;'>Добавить предмет</i>");
				renew_cats();
			});
			return false;
		});
	});
	renew_cats();
});
//THEMES.js
function renew_themes(){
	$(".theme .test-state-close").unbind('click').click(function() {
		var id=$(this).parent().attr('id').split('_')[1];
		$.post('index.php',{'ajax':1,'action':'admin_delete','id':id,'what':'theme'});
		$(this).parent().fadeOut(500);
	});
	$(".theme").unbind('dblclick').dblclick(function() {
		var el=$(this);
		var cat=el.parent().attr('id').split('_')[1];
		var oldhtml=el.html();
		el.html("<form><input type='text' class='inline-edit' value='"+el.find('label').text()+"'/></form>");
		el.find("input").focus().blur(function () {
			el.html(oldhtml);
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			var id=el.attr('id').split('_')[1];
			$.post('index.php',{'ajax':1,'action':'admin_theme','id':id,'cat':cat,'val':val}, function(response) {
				el.html($(response).find('.theme').html());
				renew_themes();
				renew_checkboxes();
			});
			return false;
		});
	});
	$(".theme .test-state-modify").unbind('click').click(function() {
		var id=$(this).parent().attr('id').split('_')[1];
		location.href='index.php?action=admin_modify&id='+id;
	});
	$(".test .test-state-stat").unbind('click').click(function() {
		var id=$(this).parent().attr('id').split('_')[1];
		location.href='index.php?action=admin_stat&id='+id;
	});
}
$(function() {
	$(".themes-sortable").disableSelection().sortable({
		placeholder: "test-placeholder ui-corner-all",
		connectWith: ".themes-sortable",
		receive : function(ev,ui){
			var cat=$(this).attr('id').split('_')[1];
			var id =ui.item.attr('id').split('_')[1];
			var val=ui.item.text();
			$.post('index.php?',{'ajax':1,'action':'admin_theme','id':id,'cat':cat,'val':val});
		},
		update : function(){
			var order = $(this).sortable('serialize');
			$.post('index.php?'+order,{'ajax':1,'action':'admin_sort','what':'theme'});
		}
	});
	$(".theme-add").click(function() {
		var el=$(this);
		var cat=el.parent().attr('id').split('_')[1];
		el.html("<form><input type='text' class='inline-edit'/></form>");
		el.find("input").focus().blur(function () {
			el.html("<i style='font-weight: normal;'>Добавить тему</i>");
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			$.post('index.php',{'ajax':1,'action':'admin_theme','id':-1,'cat':cat,'val':val}, function(response) {
				el.prev().append($(response).find('done').html());
				el.html("<i>Добавить тест</i>");
				renew_themes();
				renew_checkboxes();
			});
			return false;
		});
	});
	renew_themes();
	renew_checkboxes();
});

function renew_checkboxes()
{
	$("input.radio_theme").unbind('change').change(function(){
		$("input.check_theme").removeAttr("checked");
		var m=0;
		$.each($(this).parent().find("theme"),function(k,ui){
			if($('#check_'+$(ui).attr('theme')).length>0)
				document.getElementById('check_'+$(ui).attr('theme')).checked=true;
			var c=$('#check_'+$(ui).attr('theme')).attr('count');
			m+=parseInt(isNaN(c)?0:parseInt(c));
		});
		$( "#slider" ).slider("option",{max:m>0?m:1,value:$(this).attr('limit')});
		$("#amount").text($("#slider").slider("value"));
	});
	$("input.check_theme").unbind('change').change(function() {
		var id=$("input.radio_theme:checked").attr('id').split('_')[1];
		var theme=$(this).attr('id').split('_')[1];
		if(!$(this).is(':checked')){
			$.post("index.php",{'ajax':1,'action':'admin_tt_del','theme':theme,'id':id});
			$('theme[theme='+theme+'][test='+id+']').remove();
		}
		else {
			$.post("index.php",{'ajax':1,'action':'admin_tt_set','theme':theme,'id':id});
			$("input.radio_theme").filter(":checked").parent().append('<theme theme="'+theme+'" test="'+id+'"/>');
		}
		var max=0;
		$.each($('input.radio_theme:checked').parent().find("theme"),function(k,ui){
			var c=$('#check_'+$(ui).attr('theme')).attr('count');
			max+=parseInt(isNaN(c)?0:parseInt(c));
		});
		$( "#slider" ).slider("option","max",max>0?max:1);
	
	});
}

//MENU.js
$(function() {
	$( ".menu button#run" ).button({
            icons: {
                primary: "ui-icon-triangle-1-e"
            }
	}).click(function(){
		var id=$("input.radio_theme:checked").attr('id').split('_')[1];
		var lim=$("input.radio_theme:checked").attr('limit');
		location.replace('index.php?action=run&id='+id+'&limit='+lim);
	});
	$( ".menu button#options" ).button({
            icons: {
                primary: "ui-icon-gear",
                secondary: "ui-icon-triangle-1-s"
            },
			text: false
	});
	$( ".menu button#logout" ).button({
            icons: {
                primary: "ui-icon-power",
            }
    }).click(function(){
		location.replace('index.php?action=logout');
	});
	$( "#slider" ).slider({
			value: 1,
			min: 1,
			max: 1,
			step: 1,
			slide: function( event, ui ) {
				$("#amount").text($("#slider").slider("value"));
				var id=$("input.radio_theme:checked").attr('id').split('_')[1];
				$("input.radio_theme:checked").attr("limit", ui.value);
				$.post("index.php",{"action":"admin_test_limit","id":id,"val":ui.value,"ajax":1});	
			}
	});
	//test-results
	$( ".add-test-result" ).button({
            icons: {
                primary: "ui-icon-circle-plus",
            }
    }).click(add_test_result);
	$( ".get-test-result" ).button({
            icons: {
                primary: "ui-icon-circle-zoomin",
            }
    }).click(function(){
		$.post('index.php',{'ajax':1,'action':'admin_show_results','id':$(this).attr('id').split('_')[1]},function(r){
			$('#show-results').html($(r).find('done').html());
		});
	});
	$( ".del-test-result" ).button({
            icons: {
                primary: "ui-icon-circle-minus",
            }
    }).click(add_test_result);
	$( ".testing" ).button({
            icons: {
                primary: "ui-icon-carat-1-se",
            }
    }).click(function(){location.replace($(this).attr('href'))});
	
});
function add_test_result(){
	$(this).find('.ui-icon').toggleClass('ui-icon-circle-plus').toggleClass('ui-icon-circle-minus');
	var user=$(this).parent().attr('id').split('_')[1];
	var test=$('.test-results').attr('id').split('_')[1];
	if($(this).find('.ui-icon').hasClass('ui-icon-circle-plus')){
		$(this).find('.ui-button-text').text('Допустить к тестированию');
		$.post('index.php',{'ajax':1,'action':'admin_del','user':user,'test':test,'what':'result'});
	}
	else {
		$(this).find('.ui-button-text').text('Остановить тестирование');
		$.post('index.php',{'ajax':1,'action':'admin_result','user':user,'test':test});
	}
}
//answers.js
function renew_buttonset_admin(){
		$('#modify .qtypes').each(function(k,ui){
			$(ui).find('.qtype_'+$(ui).attr('selected')).attr('checked',true);
		});
		$('#modify .qtypes').buttonset();
		$('#modify input.qtype').unbind('change').change(function() {
			var id=$(this).parent().parent();
			$.post("index.php",{'ajax':1,'action':'admin_modify_type','type':$(this).val(),'id':id.attr('id').split('_')[1]},function(response){
				id.find(".question_answers").html($(response).find('done').html());
				renew_answers_admin();
			});
		});
		$('#modify .question_text').unbind('click').click(function(){
			var el=$(this);
			var oldhtml=el.text();
			el.html("<form><input type='text' class='inline-edit' value='"+oldhtml+"'/></form>");
			el.find("input").focus().blur(function () {
				el.html(oldhtml);
			});
			el.find("form").submit(function () {
				var val=$(this).find("input").val();
				var id=el.parent().attr('id').split('_')[1];
				$.post('index.php',{'ajax':1,'action':'admin_question','id':id,'val':val});
				el.html(val);
				return false;
			});
		});
		$('#modify button.delete_question').button({icons: {
			primary: "ui-icon-closethick"
			},
            text: false
		}).click(function() {
			var id=$(this).parent().attr('id').split('_')[1];
			$.post("index.php",{'ajax':1,'action':'admin_delete','what':'qwe','id':id});
			$("#wrapper").tabs("remove",$("#wrapper").tabs("option", "selected"));
		});
}
function renew_answers_user(){
	$("#run .answers-sortable[q_type=3]").disableSelection().sortable({
		placeholder: "test-placeholder ui-corner-all",
		update : function(){
			var order = $(this).sortable('toArray');
			var q=$('.ui-state-active a').attr('href').split('_')[1];
			$('q_question[q_question='+q+']').attr('q_correct_answer',order.join('_'));
		}
	});
	$("#run .answers-draggable").disableSelection().sortable({
		placeholder: "test-placeholder ui-corner-all",
		connectWith: ".answers-draggable",
		receive : function(ev,ui){
			var parent=$(this).attr('id').split('_')[1];
			var child = $(ui.item).attr('_id').split('_')[1];
			//удалить все пары, соответствующие child.
			if($(this).attr('q_type')!=6) $('s_solution[s_child='+child+']').remove();
			if(parent==0){
				if($(this).attr('q_type')==6)
					$(ui.item).remove();
			}
			else
			//установить пару child, parent
			{
				var q=$('.ui-state-active a').attr('href').split('_')[1];
				$('q_question[q_question='+q+']').append('<s_solution s_parent="'+parent+'" s_child="'+child+'"/>');
			}
			renew_onlyone();
		}
	});
	$("#run .answers-draggable[q_type=6] .answer" ).draggable({
		connectToSortable: ".answers-draggable",
		helper: "clone",
		revert: "invalid"
	});
	$("#run input.radio_answer").unbind('change').change(function(){
		var q=$('.ui-state-active a').attr('href').split('_')[1];
		var val=$(this).attr('id').split('_')[1];
		$("q_question[q_question="+q+"]").attr('q_correct_answer',val);
	});
	$("#run input.check_answer").unbind('change').change(function() {
		var id=$(this).attr('id').split('_')[1];
		if($(this).is(':checked')){
			var q=$('.ui-state-active a').attr('href').split('_')[1];
			$('q_question[q_question='+q+']').append('<s_solution s_parent="'+id+'" s_child="0"/>');
		}else{
			$('s_solution[s_parent='+id+'][s_child=0]').remove();
		}
	});
	$("button#check").button({
            icons: {
                primary: "ui-icon-triangle-1-e"
            }
	}).click(function(){
		arr=[];
		var id=$('solutions').attr('id');
		$('q_question').each(function(k,v){
			s=[$(v).attr('q_question'),$(v).attr('q_type'),$(v).attr('q_correct_answer')]
			$.each($(v).find('s_solution'),function(k2,v2){
				s.push($(v2).attr('s_parent')+'_'+$(v2).attr('s_child'));
			});
			arr.push(s.join('.'));
		});
		$.post("index.php",{'ajax':1,'action':'check','val':arr.join(','),'id':$('#tab-default').attr('theme')},function(res){
			$('#tab-default').html($(res).find('done').html());
		});
	});
	
}
function renew_answers_admin(){
	$("#modify .answers-sortable[q_type=3]").disableSelection().sortable({
		placeholder: "test-placeholder ui-corner-all",
		connectWith: ".answers-sortable-1",
		update : function(){
			var q=$('.ui-state-active a').attr('href').split('_')[1];
			var order = $(this).sortable('serialize');
			var arr = $(this).sortable('toArray');
			
			$.post('index.php?',{'ajax':1,'action':'admin_modify_correct','val':arr.join('_'),'id':q});
			$.post('index.php?'+order,{'ajax':1,'action':'admin_sort','what':'ans'});
		}
	});
	$("#modify .answers-draggable").disableSelection().sortable({
		placeholder: "test-placeholder ui-corner-all",
		connectWith: ".answers-draggable",
		receive : function(ev,ui){
			var parent=$(this).attr('id').split('_')[1];
			var child = $(ui.item).attr('_id').split('_')[1];
			//удалить все пары, соответствующие child.
			if($(this).attr('q_type')!=6)
				$('s_solution[s_child='+child+']').remove();
			if(parent==0){
				if($(this).attr('q_type')==6)
					$(ui.item).remove();
			}
			else
			//установить пару child, parent
			{
				var q=$('.ui-state-active a').attr('href').split('_')[1];
				$('q_question[q_question='+q+']').append('<s_solution s_parent="'+parent+'" s_child="'+child+'"/>');
			}
			//послать решения на сервер
			post_solutions();
			renew_onlyone();
		}
	});
	$( "#modify .answers-draggable[q_type=6] .answer" ).draggable({
		connectToSortable: ".answers-draggable",
		helper: "clone",
		revert: "invalid"
	});
	$("#modify .answer-add").click(function() {
		var el=$(this);
		var type=el.attr('type');
		var q_type=el.attr('q_type');
		var question=el.attr('question');
		el.html("<form><input type='text' class='inline-edit'/></form>");
		el.find("input").focus().blur(function () {
			el.html("<i>Добавить ответ</i>");
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			$.post('index.php',{'ajax':1,'action':'admin_answer','id':-1,'val':val,'type':type,'question':question,'q_type':q_type}, function(response) {
				el.parent().find('.answers-sortable').append($(response).find('done').html());
				el.html("<i>Добавить ответ</i>");
				renew_answers_admin();
			});
			return false;
		});
	});
	
	$("#modify .answer .test-state-close").unbind('click').click(function() {
		var ui=$(this).parent();
		if(ui.hasClass('ui-widget-header')) ui=ui.parent();
		var id=ui.attr('id').split('_')[1];
		$.post('index.php',{'ajax':1,'action':'admin_delete','id':id,'what':'ans'});
		ui.fadeOut(500);
	});
	$("#modify .answer").unbind('dblclick').dblclick(function() {
		var el=$(this);
		var oldhtml=el.html();
		el.html("<form><input type='text' class='inline-edit' value='"+el.find('label').text()+"'/></form>");
		el.find("input").focus().blur(function () {
			el.html(oldhtml);
		});
		el.find("form").submit(function () {
			var val=$(this).find("input").val();
			var id=el.attr('id').split('_')[1];
			var q_type=el.parent().attr('q_type');
			var a_type=el.parent().attr('a_type');
			$.post('index.php',{'ajax':1,'action':'admin_answer','id':id,'val':val,'q_type':q_type,'type':a_type}, function(response) {
				el.html($(response).find('.answer').html());
				renew_answers_admin();
			});
			return false;
		});
	});
	$("#modify input.radio_answer").unbind('change').change(function(){
		//обновляем коррект и все
		var q=$('.ui-state-active a').attr('href').split('_')[1];
		$.post('index.php?',{'ajax':1,'action':'admin_modify_correct','id':q,'val':$(this).attr('id').split('_')[1]});
	});
	$("#modify input.check_answer").unbind('change').change(function() {
		var id=$(this).attr('id').split('_')[1];
		if($(this).is(':checked')){
			var q=$('.ui-state-active a').attr('href').split('_')[1];
			$('q_question[q_question='+q+']').append('<s_solution s_parent="'+id+'" s_child="0"/>');
			post_solutions();
		}else{
			$('s_solution[s_parent='+id+'][s_child=0]').remove();
			post_solutions();
		}
	});
}
function renew_onlyone(){
	$('.only-one-child').each(function(k,v){
		if($(v).find('.answer').length==1)
			$(v).removeClass('answers-draggable');
		if($(v).find('.answer').length==0)
			$(v).addClass('answers-draggable');
	});
}
function post_solutions(){
	arr=[];
	var id=$('solutions').attr('id');
	$('s_solution').each(function(k,v){
		var s_p=$(v).attr('s_parent');
		if(s_p=='')return;
		var s_q=$(v).parent().attr('q_question');
		var s_c=$(v).attr('s_child');
		arr.push(s_q+'_'+s_p+'_'+s_c);
	});
	$.post("index.php?s[]="+arr.join('&s[]='),{'ajax':1,'action':'admin_save_solutions','id':id});
}
function renew_solutions(){
//на текущей вкладке!!!
	$("input.radio_answer").each(function(k,v){v.checked=false;});
	$("input.check_answer").each(function(k,v){v.checked=false;});
	$('s_solution').each(function(k,v){
		var q_type=$(v).attr('q_type');
		if(q_type==1){
			var q_correct=$(v).attr('q_correct_answer');
			if($('#radio_'+q_correct).length)
				$('#radio_'+q_correct)[0].checked=true;
				//$('#radio_'+q_correct).attr('checked','checked');
			return;
		}
		if(q_type==3){
			//DELETE ME
		}
		var s_parent=$(v).attr('s_parent');
		if(!s_parent)return;
		if(q_type==2){
			if($('#check_'+s_parent).length)
				$('#check_'+s_parent)[0].checked=true;
			return;
		}
		var s_child=$(v).attr('s_child');
		if(q_type==4||q_type==5){
			$('#answer_'+s_child).appendTo('#sort_'+s_parent);
		}
		//todo:delete link when hit delete!!!!!!
		var s_solution=$(v).attr('s_solution');
		if(q_type==6){
			$('#answer_'+s_child).clone().appendTo('#sort_'+s_parent);
		}
	});
	
}
$(function() {
	$('#wrapper').tabs();
	$('#tab-add').unbind('click').click(function() {
		var theme=$(this).attr('theme');
		$.post("index.php",{'ajax':1,'action':'admin_question','theme':theme,'id':'-1'},function(response){
			var id=$(response).find(".question").attr('id');
			$('#wrapper').append($(response).find("done").html());
			var len=$('#wrapper').tabs("length");
			$('#wrapper').tabs("add","#"+id, len,len-1);
			renew_buttonset_admin();
		});
	});
	renew_answers_admin();
	renew_answers_user();
	renew_buttonset_admin();
	renew_solutions();
	renew_onlyone();
});

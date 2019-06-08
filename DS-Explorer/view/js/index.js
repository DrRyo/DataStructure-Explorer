var rfObj, fObj;

var menu = [{
    name: 'Folder',
    title: 'Folder Menu',
    subMenu: [{
        name: 'Add New',
        title: 'It will add folder',
        fun: function () {
            alert('It will add folder')
        }
    }, {
        name: 'Replace',
        title: 'It will replace folder',
        fun: function() {
            alert('It will replace folder')
        }
    }]
}]

$('body').contextMenu(menu);

$(function () {
    $.contextMenu({
        selector: 'span.navbar-toggler', 
        trigger: 'left',
        callback: function(key, options) {
            var m = "clicked: " + key;
            window.console && console.log(m) || alert(m); 
        },
        items: {
            folder: {
                name: "Add Folder",
                icon: "fa-folder-o",
                callback: function(key, opt) {
                    $('#inputModal').on('show.bs.modal', function(e) {
                        var modal = $(this);
                        modal.find('.modal-title').text('New Folder');
                        modal.find('input').val('');
                    });

                    $('#inputModal').on('shown.bs.modal', function(e) {
                        var modal = $(this);
                        modal.find('input').trigger('focus');
                    });

                    $('#inputModal').modal('show');

                    $('#inputModal').on('hide.bs.modal', function(e) {
                        var modal = $(this);
                        if (modal.find('input').val().length !== 0) {
                            NewFolder(modal.find('input').val());
                        }
                    });
                }
            },
            file: {
                name: "Add File",
                icon: "fa-file-o",
                callback: function(key, opt) {
                    $('#inputModal').on('show.bs.modal', function(e) {
                        var modal = $(this);
                        modal.find('.modal-title').text('New File');
                        modal.find('input').val('');
                    });

                    $('#inputModal').on('shown.bs.modal', function(e) {
                        var modal = $(this);
                        modal.find('input').trigger('focus');
                    });

                    $('#inputModal').modal('show');

                    $('#inputModal').on('hide.bs.modal', function(e) {
                        var modal = $(this);
                        if (modal.find('input').val().length !== 0) {
                            var arr = modal.find('input').val().split('.');
                            var extension = arr.pop();
                            var filename = arr.join('.');

                            NewFile(filename, extension);
                        }
                    });
                }
            }
        }
    });
});

function UpdateRootFolderObject(rfObj) {
    rfObj = this;
}

function UpdateCurrentFolderObject(fObj) {
    $('textarea#debug').val($('textarea#debug').val() + "\r\n" + JSON.stringify(this));
    $('textarea#debug').val($('textarea#debug').val() + "\r\n" + JSON.stringify(fObj));
    fObj = this;
    UpdateUI(this, fObj);
}

var $parent = $(`<tr>
    <th scope="row"></th>
    <td>..</td>
    <td></td>
    <td></td>
    <td></td>
</tr>`);

var $folder = $(`<tr>
    <th scope="row"><i class="fa fa-folder-open"></i></th>
</tr>`);

var $file = $(`<tr>
    <th scope="row"><i class="fa fa-file-o"></i></th>
</tr>`);

function UpdateUI(obj, fObj) {
    $('tbody').empty();
    $('tbody').append($parent.clone());

    $.each(obj.folderList, function(idx, val) {
        var child = $folder.clone();

        $('tbody').append(
            child.append($(`
                <td>` + val.name + `</td>
                <td>` + val.accessDate + `</td>
                <td>` + val.modifyDate + `</td>
                <td>` + val.createDate + `</td>
                <td class="button-td"><button type="button" class="btn btn-success btn-sm"><i class="fa fa-edit"></i></button></td>
                <td class="button-td"><button type="button" class="btn btn-danger btn-sm"><i class="fa fa-trash-o"></i></button></td>
            `).clone())
        );
    });
    
    $.each(obj.fileList, function(idx, val) {
        var child = $file.clone();
        
        $('tbody').append(
            child.append($(`
                <td>` + val.name + `.` + val.extension + `</td>
                <td>` + val.accessDate + `</td>
                <td>` + val.modifyDate + `</td>
                <td>` + val.createDate + `</td>
                <td class="button-td"><button type="button" class="btn btn-success btn-sm"><i class="fa fa-edit"></i></button></td>
                <td class="button-td"><button type="button" class="btn btn-danger btn-sm"><i class="fa fa-trash-o"></i></button></td>                
            `).clone())
        );
    });
}
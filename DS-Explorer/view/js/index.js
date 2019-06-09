var rfObj, fObj;

$(function () {
    $.contextMenu({
        selector: 'span.navbar-toggler', 
        trigger: 'left',
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

    UpdateClickEvent();
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

var $parent = $(`<tr data-type="parent">
    <th scope="row"></th>
    <td>..</td>
    <td></td>
    <td></td>
    <td></td>
</tr>`);

var $folder = $(`<tr data-type="folder">
    <th scope="row"><i class="fa fa-folder-open"></i></th>
</tr>`);

var $file = $(`<tr data-type="file">
    <th scope="row"><i class="fa fa-file-o"></i></th>
</tr>`);

function UpdateUI(obj, fObj) {
    $('tbody').empty();
    $('tbody').append($parent.clone());

    $.each(obj.folderList, function(idx, val) {
        var child = $folder.clone();

        $('tbody').append(
            child.append($(`
                <td class="name">` + val.name + `</td>
                <td>` + val.accessDate + `</td>
                <td>` + val.modifyDate + `</td>
                <td>` + val.createDate + `</td>
                <td class="button-td">
                    <button type="button"
                        class="btn btn-success btn-sm btn-edit"
                        data-location="` + val.location + `"
                        data-name="` + val.name + `">
                        <i class="fa fa-edit"></i>
                    </button>
                </td>
                <td class="button-td">
                    <button type="button"
                        class="btn btn-danger btn-sm btn-delete"
                        data-location="` + val.location + `"
                        data-name="` + val.name + `">
                        <i class="fa fa-trash-o"></i>
                    </button>
                </td>
            `).clone())
        );
    });
    
    $.each(obj.fileList, function(idx, val) {
        var child = $file.clone();
        
        $('tbody').append(
            child.append($(`
                <td class="name">` + val.name + `.` + val.extension + `</td>
                <td>` + val.accessDate + `</td>
                <td>` + val.modifyDate + `</td>
                <td>` + val.createDate + `</td>
                <td class="button-td">
                    <button type="button"
                        class="btn btn-success btn-sm btn-edit"
                        data-location="` + val.location + `"
                        data-name="` + val.name + `"
                        data-extension="` + val.extension + `">
                        <i class="fa fa-edit"></i>
                    </button>
                </td>
                <td class="button-td">
                    <button type="button"
                        class="btn btn-danger btn-sm btn-delete"
                        data-location="` + val.location + `"
                        data-name="` + val.name + `"
                        data-extension="` + val.extension + `">
                        <i class="fa fa-trash-o"></i>
                    </button>
                </td>
            `).clone())
        );
    });

    UpdateClickEvent();
}

function UpdateClickEvent() {
    UpdateDoubleClickEvent();
    UpdateEditEvent();
    UpdateDeleteEvent();
}

function UpdateDoubleClickEvent() {
    $('tr').off();
    $('tr').click(function() {
        if ($(this).find('th').attr("clicked") === undefined
        || $(this).find('th').attr("clicked") === "") {
            $(this).find('th').attr("clicked", "true");
            console.log("clicked first!");
        } else {
            $(this).find('th').attr("clicked", "");
            console.log("clicked second!");

            var type = $(this).data('type');

            if (type === "folder") {
                var name = $(this).find('td.name').text();
                console.log(name);
                OpenFolder(name);
            } else if (type === "file") {
                var arr = $(this).find('td.name').text().split('.');
                console.log(arr);
                var extension = arr.pop();
                var name = arr.join('.');
                OpenFile(name, extension);
            } else {
                // parent
                MoveToParentFolder();
            }
        }
    });
}

function UpdateEditEvent() {
    $('button.btn-edit').off();
    $('button.btn-edit').click(function() {
        var name = $(this).data("name");
        var extension = $(this).data("extension");
        var location = $(this).data("location");

        if (extension === "") {
            $('#inputModal').on('show.bs.modal', function(e) {
                var modal = $(this);
                modal.find('.modal-title').text('Rename Folder "' + name + '" to ...');
                modal.find('input').val('');
            });

            $('#inputModal').on('shown.bs.modal', function(e) {
                var modal = $(this);
                modal.find('input').trigger('focus');
            });

            $('#inputModal').on('hide.bs.modal', function(e) {
                var modal = $(this);
                if (modal.find('input').val().length !== 0) {
                    RenameFolder(modal.find('input').val());
                }
            });

            $('#inputModal').modal('show');
        } else {

        }
    });
}

function UpdateDeleteEvent() {
    $('button.btn-delete').off();
    $('button.btn-delete').click(function() {
        $('#inputModal').on('show.bs.modal', function(e) {
            var modal = $(this);
            modal.find('.modal-title').text('New Folder');
            modal.find('input').val('');
        });

        $('#inputModal').on('shown.bs.modal', function(e) {
            var modal = $(this);
            modal.find('input').trigger('focus');
        });

        $('#inputModal').on('hide.bs.modal', function(e) {
            var modal = $(this);
            if (modal.find('input').val().length !== 0) {
                DeleteFolder(modal.find('input').val());
            }
        });

        $('#inputModal').modal('show');
    });
}
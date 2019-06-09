var rfObj, fObj;

$(function () {
  $('div.btn-debug').click(function () {
    $('#debugModal').modal('show');
  });

  $.contextMenu({
    selector: 'span.navbar-toggler',
    trigger: 'left',
    items: {
      folder: {
        name: "Add Folder",
        icon: "fa-folder-o",
        callback: function (key, opt) {
          $('#inputModal').on('show.bs.modal', function (e) {
            var modal = $(this);
            modal.find('.modal-title').text('New Folder');
            modal.find('input').val('');
          });

          $('#inputModal').on('shown.bs.modal', function (e) {
            var modal = $(this);
            modal.find('input').trigger('focus');
          });

          $('#inputModal').modal('show');

          $('#inputModal').on('hide.bs.modal', function (e) {
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
        callback: function (key, opt) {
          $('#inputModal').on('show.bs.modal', function (e) {
            var modal = $(this);
            modal.find('.modal-title').text('New File');
            modal.find('input').val('');
          });

          $('#inputModal').on('shown.bs.modal', function (e) {
            var modal = $(this);
            modal.find('input').trigger('focus');
          });

          $('#inputModal').modal('show');

          $('#inputModal').on('hide.bs.modal', function (e) {
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

  $.contextMenu({
    selector: '.btn-menu.btn-folder',
    trigger: 'left',
    items: {
      rename: {
        name: "Rename",
        icon: "fa-edit",
        callback: function (key, opt) {

        }
      },
      delete: {
        name: "Delete",
        icon: "fa-trash",
        callback: function (key, opt) {

        }
      },
      copy: {
        name: "Copy",
        icon: "fa-copy",
        callback: function (key, opt) {

        }
      },
      cut: {
        name: "Cut",
        icon: "fa-cut",
        callback: function (key, opt) {

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
  log(this, true);
  fObj = this;
  UpdateUI(this);
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

function UpdateUI(obj) {
  $('table#table-explorer').DataTable().clear().destroy();

  var mdfFileList = [];

  $.each(obj.fileList, function(idx, val) {
    mdfFileList.push({
      type: 'file',
      name: val.name + "." + val.extension,
      accessDate: val.accessDate,
      modifyDate: val.modifyDate,
      createDate: val.createDate
    });
  });

  var arr = obj.folderList.concat(mdfFileList);
  arr.push({
    type: 'parent',
    name: '..',
    accessDate: '',
    modifyDate: '',
    createDate: ''
  });

  var table = $('table#table-explorer').DataTable({
    responsive: false,
    paging: false,
    data: arr,
    order: [[0, "asc"], [1, "asc"]],
    createdRow: function(row, data, dataIndex) {
      console.log(data.type);
      if (data.type === 'folder') {
        $(row).attr('data-type', 'folder');
      } else if (data.type === 'file') {
        $(row).attr('data-type', 'file');
      } else {
        $(row).attr('data-type', 'parent');
      }
    },
    columns: [
      { data: "type" },
      { data: "name" },
      { data: "accessDate" },
      { data: "modifyDate" },
      { data: "createDate" },
      { data: "type" }
    ],
    columnDefs: [
      {
        targets: 0,
        searchable: false,
        render: function (data, type, full, meta) {
          if (data === 'folder') {
            return `<i class="fa fa-folder-open"></i><span style="display:none;">1</span>`;
          } else if (data === 'file') {
            return `<i class="fa fa-file-o"></i><span style="display:none;">2</span>`;
          } else {
            return `<span style="display:none;">0</span>`;
          }
        }
      },
      {
        targets: 1,
        className: 'name'
      },
      {
        targets: -1,
        title: 'Menu',
        className: 'button-td',
        orderable: false,
        searchable: false,
        render: function (data, type, full, meta) {
          if (data !== 'parent') {
            return `<div class="btn btn-secondary btn-sm btn-menu btn-folder btn-td">
                  <i class="fa fa-bars"></i>
                </div>`;
          } else {
            return ``;
          }
        }
      }
    ],
    initComplete: function(settings, json) {
      UpdateClickEvent();
    }
  });

  UpdateClickEvent();
}

function UpdateClickEvent() {
  UpdateDoubleClickEvent();
  UpdateEditEvent();
  UpdateDeleteEvent();
  UpdateContextMenu();
}

function UpdateDoubleClickEvent() {
  $('tr').off();
  $('tr').click(function () {
    if ($(this).find('td:first-child').attr("clicked") === undefined
      || $(this).find('td:first-child').attr("clicked") === "") {
      var _this = $(this);
      $(this).find('td:first-child').attr("clicked", "true");
      setTimeout(function () {
        _this.find('td:first-child').attr("clicked", "");
        log("clicked disabled!");
      }, 600);
      log("clicked first!");
    } else {
      $(this).find('td:first-child').attr("clicked", "");
      log("clicked second!");

      var type = $(this).data('type');

      if (type === "folder") {
        var name = $(this).find('td.name').text();
        log(name);
        OpenFolder(name);
      } else if (type === "file") {
        var arr = $(this).find('td.name').text().split('.');
        log(arr);
        var extension = arr.pop();
        var name = arr.join('.');
        OpenFile(name, extension);
      } else if (type === "parent") {
        // parent
        MoveToParentFolder();
      }
    }
  });
}

function UpdateEditEvent() {
  $('button.btn-edit').off();
  $('button.btn-edit').click(function () {
    var name = $(this).data("name");
    var extension = $(this).data("extension");
    var location = $(this).data("location");

    if (extension === undefined ||
      extension === "") {
      $('#inputModal').on('show.bs.modal', function (e) {
        var modal = $(this);
        modal.find('.modal-title').text('Rename Folder "' + name + '" to ...');
        modal.find('input').val('');
        modal.find('div.modal-footer > button').text('Edit');
      });

      $('#inputModal').on('shown.bs.modal', function (e) {
        var modal = $(this);
        modal.find('input').trigger('focus');
      });

      $('#inputModal').on('hide.bs.modal', function (e) {
        var modal = $(this);
        if (modal.find('input').val().length !== 0) {
          log("Change `" + name + "` to `"
            + modal.find('input').val() + "`");
          RenameFolder(name, modal.find('input').val());
        }
      });

      $('#inputModal').modal('show');
    } else {
      $('#inputModal').on('show.bs.modal', function (e) {
        var modal = $(this);
        modal.find('.modal-title').text('Rename File "'
          + name + "." + extension + '" to ...');
        modal.find('input').val('');
        modal.find('div.modal-footer > button').text('Edit');
      });

      $('#inputModal').on('shown.bs.modal', function (e) {
        var modal = $(this);
        modal.find('input').trigger('focus');
      });

      $('#inputModal').on('hide.bs.modal', function (e) {
        var arr = $(this).find('input').val().split('.');
        var Textension = arr.pop();
        var Tname = arr.join('.');

        if (modal.find('input').val().length !== 0) {
          log("Change `" + name + "." + extension + "` to `"
            + Tname + "." + Textension + "`");
          RenameFile(name, extension, Tname, Textension);
        }
      });

      $('#inputModal').modal('show');
    }
  });
}

function UpdateDeleteEvent() {
  $('button.btn-delete').off();
  $('button.btn-delete').click(function () {
    $('#inputModal').on('show.bs.modal', function (e) {
      var modal = $(this);
      modal.find('.modal-title').text('New Folder');
      modal.find('input').val('');
    });

    $('#inputModal').on('shown.bs.modal', function (e) {
      var modal = $(this);
      modal.find('input').trigger('focus');
    });

    $('#inputModal').on('hide.bs.modal', function (e) {
      var modal = $(this);
      if (modal.find('input').val().length !== 0) {
        DeleteFolder(modal.find('input').val());
      }
    });

    $('#inputModal').modal('show');
  });
}

function UpdateContextMenu() {
  //$.contextMenu('update');
}

function log(msg, clr = false) {
  if (clr) {
    $('#debug').text(JSON.stringify(msg));
  } else {
    $('#debug').text(
      JSON.stringify(msg)
      + "\r\n"
      + $('#debug').text());
  }
}

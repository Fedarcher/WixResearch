namespace MyAddin1
{
    partial class AddinModule
    {
        /// <summary>
        /// Required by designer
        /// </summary>
        private System.ComponentModel.IContainer components;
 
        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code
        /// <summary>
        /// Required by designer support - do not modify
        /// the following method
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            //
            // AddinModule
            //
            this.AddinName = "MyAddin1";
            
            this.SupportedApps = ((AddinExpress.MSO.ADXOfficeHostApp)(
				AddinExpress.MSO.ADXOfficeHostApp.ohaOutlook 
				));
        }
        #endregion
    }
}


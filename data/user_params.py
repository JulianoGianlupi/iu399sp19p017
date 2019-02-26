 
# This file is auto-generated from a Python script that parses a PhysiCell configuration (.xml) file.
#
# Edit at your own risk.
#
import os
from ipywidgets import Label,Text,Checkbox,Button,HBox,VBox,FloatText,IntText,BoundedIntText,BoundedFloatText,Layout,Box
    
class UserTab(object):

    def __init__(self):
        
        micron_units = Label('micron')   # use "option m" (Mac, for micro symbol)

        constWidth = '180px'
        tab_height = '500px'
        stepsize = 10

        #style = {'description_width': '250px'}
        style = {'description_width': '25%'}
        layout = {'width': '400px'}

        name_button_layout={'width':'25%'}
        widget_layout = {'width': '15%'}
        units_button_layout ={'width':'15%'}
        desc_button_layout={'width':'45%'}

        param_name1 = Button(description='random_seed', disabled=True, layout=name_button_layout)
        param_name1.style.button_color = 'tan'

        self.random_seed = IntText(
          value=0,
          step=1,
          style=style, layout=widget_layout)

        param_name2 = Button(description='motile_cell_persistence_time', disabled=True, layout=name_button_layout)
        param_name2.style.button_color = 'tan'

        self.motile_cell_persistence_time = FloatText(
          value=15,
          step=1,
          style=style, layout=widget_layout)

        param_name3 = Button(description='motile_cell_migration_speed', disabled=True, layout=name_button_layout)
        param_name3.style.button_color = 'tan'

        self.motile_cell_migration_speed = FloatText(
          value=0.5,
          step=0.1,
          style=style, layout=widget_layout)

        param_name4 = Button(description='motile_cell_relative_adhesion', disabled=True, layout=name_button_layout)
        param_name4.style.button_color = 'tan'

        self.motile_cell_relative_adhesion = FloatText(
          value=0.05,
          step=0.01,
          style=style, layout=widget_layout)

        param_name5 = Button(description='motile_cell_apoptosis_rate', disabled=True, layout=name_button_layout)
        param_name5.style.button_color = 'tan'

        self.motile_cell_apoptosis_rate = FloatText(
          value=0.0,
          step=0.01,
          style=style, layout=widget_layout)

        param_name6 = Button(description='motile_cell_relative_cycle_entry_rate', disabled=True, layout=name_button_layout)
        param_name6.style.button_color = 'tan'

        self.motile_cell_relative_cycle_entry_rate = FloatText(
          value=0.1,
          step=0.01,
          style=style, layout=widget_layout)

        param_name7 = Button(description='birth_interval', disabled=True, layout=name_button_layout)
        param_name7.style.button_color = 'tan'

        self.birth_interval = FloatText(
          value=60,
          step=1,
          style=style, layout=widget_layout)

        param_name8 = Button(description='volume_total', disabled=True, layout=name_button_layout)
        param_name8.style.button_color = 'tan'

        self.volume_total = FloatText(
          value=1,
          step=0.1,
          style=style, layout=widget_layout)

        param_name9 = Button(description='target_fluid_frac', disabled=True, layout=name_button_layout)
        param_name9.style.button_color = 'tan'

        self.target_fluid_frac = FloatText(
          value=0.75,
          step=0.1,
          style=style, layout=widget_layout)

        param_name10 = Button(description='fluid_change_rate', disabled=True, layout=name_button_layout)
        param_name10.style.button_color = 'tan'

        self.fluid_change_rate = FloatText(
          value=0.15,
          step=0.01,
          style=style, layout=widget_layout)

        param_name11 = Button(description='cytoplasmic_biomass_change_rate', disabled=True, layout=name_button_layout)
        param_name11.style.button_color = 'tan'

        self.cytoplasmic_biomass_change_rate = FloatText(
          value=0.15,
          step=0.01,
          style=style, layout=widget_layout)

        units_button1 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button1.style.button_color = 'tan'
        units_button2 = Button(description='min', disabled=True, layout=units_button_layout) 
        units_button2.style.button_color = 'tan'
        units_button3 = Button(description='micron/min', disabled=True, layout=units_button_layout) 
        units_button3.style.button_color = 'tan'
        units_button4 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button4.style.button_color = 'tan'
        units_button5 = Button(description='1/min', disabled=True, layout=units_button_layout) 
        units_button5.style.button_color = 'tan'
        units_button6 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button6.style.button_color = 'tan'
        units_button7 = Button(description='min', disabled=True, layout=units_button_layout) 
        units_button7.style.button_color = 'tan'
        units_button8 = Button(description='micron^3', disabled=True, layout=units_button_layout) 
        units_button8.style.button_color = 'tan'
        units_button9 = Button(description='', disabled=True, layout=units_button_layout) 
        units_button9.style.button_color = 'tan'
        units_button10 = Button(description='1/min', disabled=True, layout=units_button_layout) 
        units_button10.style.button_color = 'tan'
        units_button11 = Button(description='1/min', disabled=True, layout=units_button_layout) 
        units_button11.style.button_color = 'tan'


        row0 = [param_name1, self.random_seed, units_button1, ] 
        row0 = [param_name2, self.motile_cell_persistence_time, units_button2, ] 
        row0 = [param_name3, self.motile_cell_migration_speed, units_button3, ] 
        row0 = [param_name4, self.motile_cell_relative_adhesion, units_button4, ] 
        row0 = [param_name5, self.motile_cell_apoptosis_rate, units_button5, ] 
        row0 = [param_name6, self.motile_cell_relative_cycle_entry_rate, units_button6, ] 
        row0 = [param_name7, self.birth_interval, units_button7, ] 
        row0 = [param_name8, self.volume_total, units_button8, ] 
        row0 = [param_name9, self.target_fluid_frac, units_button9, ] 
        row0 = [param_name10, self.fluid_change_rate, units_button10, ] 
        row0 = [param_name11, self.cytoplasmic_biomass_change_rate, units_button11, ] 

        box_layout = Layout(display='flex', flex_flow='row', align_items='stretch', width='100%')
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)
        box0 = Box(children=row0, layout=box_layout)

        self.tab = VBox([
          box0,
          box0,
          box0,
          box0,
          box0,
          box0,
          box0,
          box0,
          box0,
          box0,
          box0,
        ])

    # Populate the GUI widgets with values from the XML
    def fill_gui(self, xml_root):
        uep = xml_root.find('.//user_parameters')  # find unique entry point into XML
        self.random_seed.value = int(uep.find('.//random_seed').text)
        self.motile_cell_persistence_time.value = float(uep.find('.//motile_cell_persistence_time').text)
        self.motile_cell_migration_speed.value = float(uep.find('.//motile_cell_migration_speed').text)
        self.motile_cell_relative_adhesion.value = float(uep.find('.//motile_cell_relative_adhesion').text)
        self.motile_cell_apoptosis_rate.value = float(uep.find('.//motile_cell_apoptosis_rate').text)
        self.motile_cell_relative_cycle_entry_rate.value = float(uep.find('.//motile_cell_relative_cycle_entry_rate').text)
        self.birth_interval.value = float(uep.find('.//birth_interval').text)
        self.volume_total.value = float(uep.find('.//volume_total').text)
        self.target_fluid_frac.value = float(uep.find('.//target_fluid_frac').text)
        self.fluid_change_rate.value = float(uep.find('.//fluid_change_rate').text)
        self.cytoplasmic_biomass_change_rate.value = float(uep.find('.//cytoplasmic_biomass_change_rate').text)


    # Read values from the GUI widgets to enable editing XML
    def fill_xml(self, xml_root):
        uep = xml_root.find('.//user_parameters')  # find unique entry point into XML 
        uep.find('.//random_seed').text = str(self.random_seed.value)
        uep.find('.//motile_cell_persistence_time').text = str(self.motile_cell_persistence_time.value)
        uep.find('.//motile_cell_migration_speed').text = str(self.motile_cell_migration_speed.value)
        uep.find('.//motile_cell_relative_adhesion').text = str(self.motile_cell_relative_adhesion.value)
        uep.find('.//motile_cell_apoptosis_rate').text = str(self.motile_cell_apoptosis_rate.value)
        uep.find('.//motile_cell_relative_cycle_entry_rate').text = str(self.motile_cell_relative_cycle_entry_rate.value)
        uep.find('.//birth_interval').text = str(self.birth_interval.value)
        uep.find('.//volume_total').text = str(self.volume_total.value)
        uep.find('.//target_fluid_frac').text = str(self.target_fluid_frac.value)
        uep.find('.//fluid_change_rate').text = str(self.fluid_change_rate.value)
        uep.find('.//cytoplasmic_biomass_change_rate').text = str(self.cytoplasmic_biomass_change_rate.value)
